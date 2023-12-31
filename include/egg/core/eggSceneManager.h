#pragma once

#include <egg/core/eggColorFader.h>
#include <egg/core/eggExpHeap.h>
#include <egg/core/eggScene.h>
#include <egg/core/eggSceneCreator.h>

#include <Common.h>

namespace EGG {

class SceneManager {
public:
    enum eAfterFadeType {
        FADE_TYPE_IDLE = -1,
        FADE_TYPE_CHANGE_SCENE = 0,
        FADE_TYPE_CHANGE_SIBLING_SCENE = 1,
        FADE_TYPE_CREATE_CHILD_SCENE = 2,
        FADE_TYPE_REINITIALIZE = 3,
        FADE_TYPE_DESTROY_TO_SELECT = 4
    };

    SceneManager(SceneCreator *);
    ~SceneManager();

    virtual void calc();
    virtual void draw();
    virtual void calcCurrentScene();
    virtual void calcCurrentFader();
    virtual void drawCurrentScene();
    virtual void drawCurrentFader();
    virtual void createDefaultFader();

    bool fadeIn();
    bool fadeOut();

    void reinitCurrentScene();
    bool reinitCurrentSceneAfterFadeOut();

    void changeScene(s32 id);
    bool changeSceneAfterFadeOut(s32 id);
    void changeSiblingScene(s32 id);
    bool changeSiblingSceneAfterFadeOut(s32 id);
    void changeSiblingScene();

    void createScene(s32 id, Scene *parent);
    void createChildScene(s32 id, Scene *parent);
    bool createChildSceneAfterFadeOut(s32 id, Scene *pParent);

    bool destroyCurrentSceneNoIncoming(bool destroyRootIfNoParent);
    bool destroyCurrentScene();
    bool destroyCurrentSceneAfterFadeOut();
    bool destroyToSelectSceneID(s32 id);
    bool destroyToSelectSceneIDAfterFadeOut(s32 id);
    void destroyScene(Scene *scene);

    void incomingCurrentScene();

    void setupNextSceneID();
    void outgoingParentScene(Scene *pParent);
    Scene *findParentScene(s32 id);
    ExpHeap *getCurrentSceneExpHeap() const;
    Scene *createSceneOnly(s32 id, Scene *parent);
    void destroySceneOnly(Scene *scene);

    void resetAfterFadeType() {
        mFadeType = FADE_TYPE_IDLE;
    }

    s32 getCurrentSceneID() const {
        return mCurrentSceneId;
    }

    Scene *getCurrentScene() const {
        return mCurrentScene;
    }

    ColorFader *getCurrentFader() const {
        return mCurrentFader;
    }

    void setCreator(SceneCreator *creator) {
        mSceneCreator = creator;
    }

    void setNextSceneID(s32 id) {
        mNextSceneId = id;
    }

    void setAfterFadeType(eAfterFadeType type) {
        mFadeType = type;
    }

    static Heap *getHeapMem1_ForCreateScene() {
        return sHeapMem1_ForCreateScene;
    }

    static Heap *getHeapMem2_ForCreateScene() {
        return sHeapMem2_ForCreateScene;
    }

private:
    SceneCreator *mSceneCreator;
    u8 _08[0x0c - 0x08];
    Scene *mCurrentScene;
    Scene *mParentScene;
    s32 mNextSceneId;
    s32 mCurrentSceneId;
    s32 mPrevSceneId;
    eAfterFadeType mFadeType;
    ColorFader *mCurrentFader;
    BOOL bUseMem2;

    static u16 sHeapOptionFlg;
    static Heap *sHeapMem1_ForCreateScene;
    static Heap *sHeapMem2_ForCreateScene;
};

} // namespace EGG
