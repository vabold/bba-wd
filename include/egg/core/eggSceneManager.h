#pragma once

#include <egg/core/eggColorFader.h>
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
    FADE_TYPE_OUTGOING = 2,
    FADE_TYPE_REINITIALIZE = 3,
    FADE_TYPE_INCOMING = 4
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
  bool createChildSceneAfterFadeOut(s32 id, Scene *parent);
  bool destroyCurrentScene();
  bool destroyToSelectSceneID(s32 id);
  bool destroyCurrentSceneNoIncoming(bool destroyRootIfNoParent);
  void destroyScene(Scene *scene);
  void incomingCurrentScene();

  void setupNextSceneID();
  void outgoingParentScene(Scene *parent);
  Scene *findParentScene(s32 id);
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
    mCreator = creator;
  }

  void setNextSceneID(s32 id) {
    mNextSceneId = id;
  }

  void setAfterFadeType(eAfterFadeType type) {
    mFadeType = type;
  }

private:
  SceneCreator *mCreator;
  u8 _08[0x0c - 0x08];
  Scene *mCurrentScene;
  Scene *pParent;
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
