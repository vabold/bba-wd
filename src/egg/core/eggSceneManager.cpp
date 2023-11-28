#include <egg/core/eggSceneManager.h>

#include <egg/core/eggDisplay.h>
#include <egg/core/eggExpHeap.h>
#include <egg/core/eggSystem.h>

#include <sdk/GXMisc.h>

namespace EGG {

SceneManager::SceneManager(SceneCreator *creator) {
    mCreator = creator;
    mCurrentScene = NULL;
    mPrevSceneId = -1;
    mCurrentSceneId = -1;
    mNextSceneId = -1;
    mFadeType = FADE_TYPE_IDLE;
    mCurrentFader = NULL;
    bUseMem2 = TRUE;
    createDefaultFader();
}

SceneManager::~SceneManager() {}

bool SceneManager::fadeIn() {
    return mCurrentFader->fadeIn();
}

bool SceneManager::fadeOut() {
    return mCurrentFader->fadeOut();
}

void SceneManager::calc() {
    calcCurrentScene();
    calcCurrentFader();
}

void SceneManager::draw() {
    drawCurrentScene();
    drawCurrentFader();
}

void SceneManager::reinitCurrentScene() {
    if (mCurrentScene) {
        mCurrentScene->reinit();
    }
}

bool SceneManager::reinitCurrentSceneAfterFadeOut() {
    bool fadedOut = false;

    if (mFadeType == FADE_TYPE_IDLE && fadeOut()) {
        setAfterFadeType(FADE_TYPE_REINITIALIZE);
        fadedOut = true;
    }

    return fadedOut;
}

void SceneManager::changeScene(s32 id) {
    while (mCurrentScene) {
        destroyCurrentSceneNoIncoming(true);
    }

    changeSiblingScene(id);
}

bool SceneManager::changeSceneAfterFadeOut(s32 id) {
    // Unknown function body
}

void SceneManager::changeSiblingScene(s32 id) {
    setNextSceneID(id);
    changeSiblingScene();
}

bool SceneManager::changeSiblingSceneAfterFadeOut(s32 id) {
    bool fadedOut = false;

    if (mFadeType == FADE_TYPE_IDLE && fadeOut()) {
        setNextSceneID(id);
        setAfterFadeType(FADE_TYPE_CHANGE_SIBLING_SCENE);
        fadedOut = true;
    }

    return fadedOut;
}

void SceneManager::changeSiblingScene() {
    Scene *parent = NULL;
    if (mCurrentScene) {
        parent = mCurrentScene->getParentScene();
    }

    if (mCurrentScene) {
        destroyScene(mCurrentScene);
        mCurrentScene = NULL;
    }

    s32 nextSceneId = mNextSceneId;
    setupNextSceneID();
    createScene(nextSceneId, parent);
}

void SceneManager::createScene(s32 id, Scene *parent) {
    Heap *pParentHeap_Mem1;
    Heap *pParentHeap_Mem2;

    if (parent) {
        pParentHeap_Mem1 = parent->getHeap_Mem1();
        pParentHeap_Mem2 = parent->getHeap_Mem2();
    } else {
        BaseSystem *sys = BaseSystem::sSystem;
        pParentHeap_Mem1 = sys->mRootHeapMem1;
        pParentHeap_Mem2 = sys->mRootHeapMem2;
    }

    Heap *pParentHeap = !bUseMem2 ? pParentHeap_Mem1 : pParentHeap_Mem2;
    BOOL locked = pParentHeap->tstDisableAllocation();
    if (locked) {
        pParentHeap->enableAllocation();
    }

    ExpHeap *pNewHeap = ExpHeap::create(-1, pParentHeap, sHeapOptionFlg);

    ExpHeap *pNewHeap_Mem1;
    ExpHeap *pNewHeap_Mem2;

    if (pParentHeap == pParentHeap_Mem2) {
        pNewHeap_Mem1 = ExpHeap::create(-1, pParentHeap_Mem1, sHeapOptionFlg);
        pNewHeap_Mem2 = dynamic_cast<ExpHeap *>(pNewHeap);
    } else {
        pNewHeap_Mem2 = ExpHeap::create(-1, pParentHeap_Mem2, sHeapOptionFlg);
        pNewHeap_Mem1 = dynamic_cast<ExpHeap *>(pNewHeap);
    }

    sHeapMem1_ForCreateScene = pNewHeap_Mem1;
    sHeapMem2_ForCreateScene = pNewHeap_Mem2;

    if (locked) {
        pParentHeap->disableAllocation();
    }

    pNewHeap->becomeCurrentHeap();

    Scene *pNewScene = mCreator->create(id);

    if (parent) {
        parent->setChildScene(pNewScene);
    }

    mCurrentScene = pNewScene;
    pNewScene->setSceneID(id);
    pNewScene->setParentScene(parent);
    pNewScene->setSceneMgr(this);
    pNewScene->enter();
}

void SceneManager::createChildScene(s32 id, Scene *parent) {
    outgoingParentScene(parent);
    setNextSceneID(id);
    setupNextSceneID();
    createScene(id, parent);
}

bool SceneManager::destroyCurrentSceneNoIncoming(bool destroyRootIfNoParent) {
    bool ret = false;
    if (mCurrentScene) {
        Scene *parent = mCurrentScene->getParentScene();
        if (parent) {
            ret = true;
            destroyScene(parent->getChildScene());
            setNextSceneID(parent->getSceneID());
            setupNextSceneID();
        } else {
            if (destroyRootIfNoParent) {
                destroyScene(mCurrentScene);
                setNextSceneID(-1);
                setupNextSceneID();
            }
        }
    }

    return ret;
}

bool SceneManager::destroyCurrentScene() {
    bool ret = destroyCurrentSceneNoIncoming(false);
    if (ret) {
        incomingCurrentScene();
    }

    return ret;
}

bool SceneManager::destroyToSelectSceneID(s32 id) {
    bool ret = false;

    Scene *parent = findParentScene(id);
    if (parent) {
        ret = true;
        while (parent->getSceneID() != getCurrentSceneID()) {
            destroyCurrentSceneNoIncoming(false);
        }
        incomingCurrentScene();
    }

    return ret;
}

void SceneManager::destroyScene(Scene *pScene) {
    pScene->exit();
    GXFlush();
    GXDrawDone();

    if (pScene->getChildScene()) {
        destroyScene(pScene->getChildScene());
    }

    GXFlush();
    GXDrawDone();

    Scene *parent = pScene->getParentScene();
    mCreator->destroy(pScene->getSceneID());
    mCurrentScene = NULL;

    if (parent) {
        parent->setChildScene(NULL);
        mCurrentScene = parent;
    }

    pScene->getHeap_Mem1()->destroy();
    pScene->getHeap_Mem2()->destroy();

    Heap *nextHeap = parent ? parent->getHeap() : !bUseMem2 ? BaseSystem::sSystem->mRootHeapMem1 : BaseSystem::sSystem->mRootHeapMem2;
    GXFlush();
    GXDrawDone();
    nextHeap->becomeCurrentHeap();
    GXFlush();
    GXDrawDone();
}

void SceneManager::incomingCurrentScene() {
    if (mCurrentScene) {
        mCurrentScene->incoming_childDestroy();
    }
}

void SceneManager::calcCurrentScene() {
    if (mCurrentScene) {
        mCurrentScene->calc();
    }
}

void SceneManager::calcCurrentFader() {
    if (!mCurrentFader) {
        return;
    }

    if (!mCurrentFader->calc()) {
        return;
    }

    switch (mFadeType) {
    case FADE_TYPE_CHANGE_SCENE:
        changeScene(mNextSceneId);
        break;
    case FADE_TYPE_CHANGE_SIBLING_SCENE:
        changeSiblingScene();
        break;
    case FADE_TYPE_OUTGOING:
        outgoingParentScene(pParent);
        setupNextSceneID();
        createScene(mCurrentSceneId, pParent);
        break;
    case FADE_TYPE_INCOMING:
        destroyToSelectSceneID(mNextSceneId);
        break;
    case FADE_TYPE_REINITIALIZE:
        reinitCurrentScene();
        break;
    }

    resetAfterFadeType();
}

void SceneManager::drawCurrentScene() {
    if (mCurrentScene) {
        mCurrentScene->draw();

        BaseSystem::sSystem->getDisplay()->setBlack(false);
    }
}

void SceneManager::drawCurrentFader() {}

void SceneManager::createDefaultFader() {
    mCurrentFader = new ColorFader(0.0f, 0.0f, 640.0f, 480.0f, 0, Fader::FADER_STATUS_OPAQUE);
}

void SceneManager::setupNextSceneID() {
    mPrevSceneId = mCurrentSceneId;
    mCurrentSceneId = mNextSceneId;
    mNextSceneId = -1;
}

void SceneManager::outgoingParentScene(Scene *parent) {
    parent->outgoing_childCreate();
}

Scene *SceneManager::findParentScene(s32 id) {
    bool found = false;
    Scene *scene;

    for (scene = mCurrentScene->getParentScene(); scene; scene = scene->getParentScene()) {
        if (scene->getSceneID() == id) {
            found = true;
            break;
        }
    }

    return found ? scene : NULL;
}

Scene *SceneManager::createSceneOnly(s32 id, Scene *parent) {
    Heap *pParentHeap_Mem1;
    Heap *pParentHeap_Mem2;

    if (parent) {
        pParentHeap_Mem1 = parent->getHeap_Mem1();
        pParentHeap_Mem2 = parent->getHeap_Mem2();
    } else {
        BaseSystem *sys = BaseSystem::sSystem;
        pParentHeap_Mem1 = sys->mRootHeapMem1;
        pParentHeap_Mem2 = sys->mRootHeapMem2;
    }

    Heap *pParentHeap = !bUseMem2 ? pParentHeap_Mem1 : pParentHeap_Mem2;
    BOOL locked = pParentHeap->tstDisableAllocation();
    if (locked) {
        pParentHeap->enableAllocation();
    }

    ExpHeap *pNewHeap = ExpHeap::create(-1, pParentHeap, sHeapOptionFlg);

    ExpHeap *pNewHeap_Mem1;
    ExpHeap *pNewHeap_Mem2;

    if (pParentHeap == pParentHeap_Mem2) {
        pNewHeap_Mem1 = ExpHeap::create(-1, pParentHeap_Mem1, sHeapOptionFlg);
        pNewHeap_Mem2 = dynamic_cast<ExpHeap *>(pNewHeap);
    } else {
        pNewHeap_Mem2 = ExpHeap::create(-1, pParentHeap_Mem2, sHeapOptionFlg);
        pNewHeap_Mem1 = dynamic_cast<ExpHeap *>(pNewHeap);
    }

    sHeapMem1_ForCreateScene = pNewHeap_Mem1;
    sHeapMem2_ForCreateScene = pNewHeap_Mem2;

    if (locked) {
        pParentHeap->disableAllocation();
    }

    pNewHeap->becomeCurrentHeap();

    Scene *pNewScene = mCreator->create(id);

    pNewScene->setSceneID(id);
    pNewScene->setParentScene(parent);
    pNewScene->setSceneMgr(this);
    pNewScene->enter();
    return pNewScene;
}

void SceneManager::destroySceneOnly(Scene *pScene) {
    pScene->exit();

    if (pScene->getChildScene()) {
        destroyScene(pScene->getChildScene());
    }

    GXFlush();
    GXDrawDone();

    Scene *parent = pScene->getParentScene();
    mCreator->destroy(pScene->getSceneID());

    pScene->getHeap_Mem1()->destroy();
    pScene->getHeap_Mem2()->destroy();

    Heap *nextHeap = parent ? parent->getHeap() : !bUseMem2 ? BaseSystem::sSystem->mRootHeapMem1 : BaseSystem::sSystem->mRootHeapMem2;
    nextHeap->becomeCurrentHeap();
}

u16 SceneManager::sHeapOptionFlg;
Heap *SceneManager::sHeapMem1_ForCreateScene;
Heap *SceneManager::sHeapMem2_ForCreateScene;

} // namespace EGG
