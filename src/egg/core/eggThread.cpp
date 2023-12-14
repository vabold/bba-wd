#include <egg/core/eggThread.h>

namespace EGG {

Thread::Thread(u32 stackSize, int msgCount, int priority, Heap *heap) {
    if (!heap) {
        heap = Heap::getCurrentHeap();
    }

    mHeap = heap;
    mStackSize = ROUND_DOWN(stackSize, 0x20);
    mStack = Heap::alloc(mStackSize, 0x20, heap);
    mHandle = reinterpret_cast<OSThread *>(Heap::alloc(sizeof(OSThread), 0x20, mHeap));
    OSCreateThread(mHandle, &start, this, reinterpret_cast<u8 *>(mStack) + mStackSize, mStackSize,
            priority, 1);
    mNewHeap = NULL;
    setCommonMesgQueue(msgCount, mHeap);
    nw4r::ut::List_Append(&sThreadList, this);
}

Thread::Thread(OSThread *thread, int msgCount) : mHeap(NULL), mHandle(thread) {
    mStackSize = reinterpret_cast<u32>(thread->stackEnd) - reinterpret_cast<u32>(thread->stackBase);
    mStack = thread->stackBase;
    mNewHeap = NULL;
    setCommonMesgQueue(msgCount, Heap::getCurrentHeap());
    nw4r::ut::List_Append(&sThreadList, this);
}

void Thread::setNewHeap(Heap *heap) {
    mNewHeap = heap;
}

Thread::~Thread() {
    nw4r::ut::List_Remove(&sThreadList, this);
    if (mHeap) {
        if (!OSIsThreadTerminated(mHandle)) {
            OSDetachThread(mHandle);
            OSCancelThread(mHandle);
        }

        Heap::free(mStack, mHeap);
        Heap::free(mHandle, mHeap);
    }

    Heap::free(mMsgArray, NULL);
}

Thread *Thread::findThread(OSThread *thread) {
    Thread *node = NULL;
    while (node = reinterpret_cast<Thread *>(nw4r::ut::List_GetNext(getList(), node))) {
        if (node->getOSThread() == thread) {
            return node;
        }
    }

    return NULL;
}

void Thread::kandoTestCancelAllThread() {
    Thread *node = NULL;
    while (node = reinterpret_cast<Thread *>(nw4r::ut::List_GetNext(getList(), node))) {
        OSThread *currentThread = OSGetCurrentThread();
        if (currentThread != node->mHandle) {
            OSCancelThread(node->mHandle);
        }
    }
}

void Thread::initialize() {
    nw4r::ut::List_Init(getList(), 0x40);
    OSSetSwitchThreadCallback(&switchThreadCallback);
}

void Thread::switchThreadCallback(OSThread *prev, OSThread *next) {
    Thread *exitingThread = findThread(prev);
    Thread *enteringThread = findThread(next);

    if (exitingThread) {
        exitingThread->onExit();
    }

    if (enteringThread) {
        enteringThread->onEnter();
    }
}

void Thread::setCommonMesgQueue(int msgCount, Heap *heap) {
    mMsgCount = msgCount;
    mMsgArray = Heap::alloc(msgCount * 4, 0x4, heap);
    OSInitMessageQueue(&mMsgQueue, mMsgArray, mMsgCount);
}

void Thread::start(void *obj) {
    Thread *thread = reinterpret_cast<Thread *>(obj);
    thread->run();
}

nw4r::ut::List Thread::sThreadList;

} // namespace EGG
