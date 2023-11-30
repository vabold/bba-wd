#include <egg/core/eggScene.h>

#include <egg/core/eggSceneManager.h>

namespace EGG {

Scene::Scene() {
    mHeap = Heap::getCurrentHeap();
    mHeap_Mem1 = SceneManager::getHeapMem1_ForCreateScene();
    mHeap_Mem2 = SceneManager::getHeapMem2_ForCreateScene();
    pParentScene = NULL;
    pChildScene = NULL;
    mId = -1;
    pSceneMgr = NULL;
}

Scene::~Scene() {}

} // namespace EGG
