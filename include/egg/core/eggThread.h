#pragma once

#include <egg/core/eggHeap.h>

#include <sdk/OSMessage.h>
#include <sdk/OSThread.h>

namespace EGG {

class Thread {
public:
    Thread(u32 stackSize, int msgCount, int priority, Heap *heap);
    Thread(OSThread *thread, int msgCount);

    virtual ~Thread();
    virtual bool run() {
        return false;
    }
    virtual void onEnter() {}
    virtual void onExit() {}

    void setNewHeap(Heap *heap);
    void setCommonMesgQueue(int msgSize, Heap *heap);

    OSThread *getOSThread() const {
        return mHandle;
    }

    Heap *getNewHeap() const {
        return mNewHeap;
    }

    static Thread *findThread(OSThread *thread);
    static void kandoTestCancelAllThread();
    static void initialize();

    static void switchThreadCallback(OSThread *prev, OSThread *next);
    static void start(void *obj);

    static nw4r::ut::List *getList() {
        return &sThreadList;
    }

private:
    Heap *mHeap;
    OSThread *mHandle;
    OSMessageQueue mMsgQueue;
    void *mMsgArray;
    s32 mMsgCount;
    void *mStack;
    u32 mStackSize;
    Heap *mNewHeap;
    nw4r::ut::Link mLink;

    static nw4r::ut::List sThreadList;
};

} // namespace EGG
