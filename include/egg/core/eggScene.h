#pragma once

#include <egg/core/eggHeap.h>

namespace EGG {

class SceneManager;

class Scene {
public:
    virtual ~Scene();
    virtual void calc() {}
    virtual void draw() {}
    virtual void enter() {}
    virtual void exit() {}
    virtual void reinit() {}
    virtual void incoming_childDestroy() {}
    virtual void outgoing_childCreate() {}

    Heap *getHeap() const {
        return mHeap;
    }
    Heap *getHeap_Mem1() const {
        return mHeap_Mem1;
    }
    Heap *getHeap_Mem2() const {
        return mHeap_Mem2;
    }
    Scene *getParentScene() {
        return pParentScene;
    }
    Scene *getChildScene() {
        return pChildScene;
    }
    s32 getSceneID() {
        return mId;
    }

    void setParentScene(Scene *scene) {
        pParentScene = scene;
    }
    void setChildScene(Scene *scene) {
        pChildScene = scene;
    }
    void setSceneID(s32 id) {
        mId = id;
    }
    void setSceneMgr(SceneManager *mgr) {
        pSceneMgr = mgr;
    }

private:
    u8 _04[0x10 - 0x04];
    Heap *mHeap;
    Heap *mHeap_Mem1;
    Heap *mHeap_Mem2;
    Scene *pParentScene;
    Scene *pChildScene;
    int mId;
    SceneManager *pSceneMgr;
};

} // namespace EGG
