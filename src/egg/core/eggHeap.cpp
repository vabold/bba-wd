#include <egg/core/eggHeap.h>

#include <egg/core/eggThread.h>
#include <sdk/OSError.h>

namespace EGG {

void Heap::initialize() {
    nw4r::ut::List_Init(&sHeapList, 0x20);
    OSInitMutex(&sRootMutex);
    sIsHeapListInitialized = TRUE;
}

Heap::Heap(MEMiHeapHead *handle) {
    mHeapHandle = handle;
    mBlock = NULL;
    mParentHeap = NULL;
    mName = "NoName";
    mFlags = 0;
    nw4r::ut::List_Init(&mChildren, 0x8);
    OSLockMutex(&sRootMutex);
    nw4r::ut::List_Append(&sHeapList, this);
    OSUnlockMutex(&sRootMutex);
}

Heap::~Heap() {
    OSLockMutex(&sRootMutex);
    nw4r::ut::List_Remove(&sHeapList, this);
    OSUnlockMutex(&sRootMutex);
}

void *Heap::alloc(size_t size, int align, Heap *heap) {
    Heap *currentHeap = sCurrentHeap;
    Thread *thread = Thread::findThread(OSGetCurrentThread());
    if (sAllocatableThread) {
        OSGetCurrentThread();
    }

    if (thread) {
        Heap *newHeap = thread->getNewHeap();
        if (newHeap) {
            currentHeap = newHeap;
            heap = newHeap;
        }
    }

    if (sAllocatableHeap) {
        if (currentHeap && !heap) {
            heap = currentHeap;
        }

        if (heap != sAllocatableHeap) {
            OSReport("cannot allocate from heap %x(%s) : allocatable heap is %x(%s)\n", heap,
                    heap->getName(), sAllocatableHeap, sAllocatableHeap->getName());
            Heap *threadHeap = thread ? thread->getNewHeap() : NULL;
            OSReport("\tthread heap=%x\n", threadHeap);
            const char *threadHeapName = thread ?
                    thread->getNewHeap() ? thread->getNewHeap()->getName() : "none" :
                    "none";
            OSReport("\tthread heap=%s\n", threadHeapName);
            if (sErrorCallback) {
                HeapErrorArg errorArg;
                errorArg.name = "disable_but";
                errorArg.arg = sErrorCallbackArg;
                (*sErrorCallback)(errorArg);
            }

            dumpAll();
            return NULL;
        }
    }

    if (sAllocCallback) {
        HeapAllocArg allocArg;
        allocArg.heap = heap ? heap : currentHeap;
        allocArg.size = size;
        allocArg.align = align;
        allocArg.arg = sAllocCallbackArg;
        (*sAllocCallback)(allocArg);
    }

    if (heap) {
        return heap->alloc(size, align);
    }

    if (currentHeap) {
        void *block = currentHeap->alloc(size, align);
        if (!block) {
            u32 heapEnd = reinterpret_cast<u32>(currentHeap->getEndAddress());
            u32 heapFreeSize = currentHeap->getAllocatableSize(0x4);
            s32 heapSize = heapEnd - reinterpret_cast<u32>(currentHeap);
            f32 heapSizeMB = static_cast<f32>(heapSize) / 1048576.0f;
            f32 sizeMB = static_cast<f32>(size) / 1048576.0f;

            OSReport("heap (%p):(%.1fMBytes free %d)->alloc(size(%d:%.1fMBytes),%d align)\n",
                    currentHeap, heapSizeMB, heapFreeSize, size, sizeMB, align);
            dumpAll();
        }
        return block;
    }

    OSReport("cannot allocate %d from heap %x\n", size, heap);
    dumpAll();
    return NULL;
}

Heap *Heap::findHeap(MEMiHeapHead *handle) {
    Heap *heap = NULL;

    OSLockMutex(&sRootMutex);
    if (sIsHeapListInitialized) {
        Heap *node = NULL;
        while (node = reinterpret_cast<Heap *>(nw4r::ut::List_GetNext(&sHeapList, node))) {
            if (node->mHeapHandle == handle) {
                heap = node;
                break;
            }
        }
    }

    OSUnlockMutex(&sRootMutex);

    return heap;
}

Heap *Heap::findParentHeap() {
    return mParentHeap;
}

Heap *Heap::findContainHeap(const void *block) {
    Heap *heap = NULL;

    if (MEMiHeapHead *handle = MEMFindContainHeap(block)) {
        heap = findHeap(handle);
    }

    return heap;
}

void Heap::free(void *block, Heap *heap) {
    if (!heap) {
        MEMiHeapHead *handle = MEMFindContainHeap(block);
        if (!handle) {
            return;
        }

        heap = findHeap(handle);
        if (!heap) {
            return;
        }
    }

    heap->free(block);
}

void Heap::dispose() {
    Disposer *node = NULL;
    while (node = reinterpret_cast<Disposer *>(nw4r::ut::List_GetFirst(&mChildren))) {
        node->~Disposer();
    }
}

void Heap::dump() {
    // Empty function in release
}

void Heap::dumpAll() {
    Heap *heap = NULL;
    u32 mem[2] = {0, 0};

    while (heap = reinterpret_cast<Heap *>(List_GetNext(&sHeapList, heap))) {
        Heap *parent = NULL;
        u32 address = reinterpret_cast<u32>(heap->getStartAddress());
        if (address < 0x90000000) {
            mem[0] += heap->getAllocatableSize(4);
        } else {
            mem[1] += heap->getAllocatableSize(4);
        }

        while (parent = reinterpret_cast<Heap *>(List_GetNext(&sHeapList, parent))) {
            if (heap->findParentHeap() == parent) {
                break;
            }
        }
    }

    // Prevent function from being inlined when called
    (void)mem;
}

Heap *Heap::becomeCurrentHeap() {
    OSLockMutex(&sRootMutex);
    Heap *oldHeap = sCurrentHeap;
    sCurrentHeap = this;
    OSUnlockMutex(&sRootMutex);
    return oldHeap;
}

Heap *Heap::_becomeCurrentHeapWithoutLock() {
    Heap *oldHeap = sCurrentHeap;
    sCurrentHeap = this;
    return oldHeap;
}

} // namespace EGG

void *operator new(size_t size) {
    return EGG::Heap::alloc(size, 4, NULL);
}

void *operator new(size_t size, int align) {
    return EGG::Heap::alloc(size, align, NULL);
}

void *operator new(size_t size, EGG::Heap *heap, int align) {
    return EGG::Heap::alloc(size, align, heap);
}

void *operator new[](size_t size) {
    return EGG::Heap::alloc(size, 4, NULL);
}

void *operator new[](size_t size, int align) {
    return EGG::Heap::alloc(size, align, NULL);
}

void *operator new[](size_t size, EGG::Heap *heap, int align) {
    return EGG::Heap::alloc(size, align, heap);
}

void operator delete(void *block) {
    EGG::Heap::free(block, NULL);
}

void operator delete[](void *block) {
    EGG::Heap::free(block, NULL);
}

nw4r::ut::List EGG::Heap::sHeapList;
OSMutex EGG::Heap::sRootMutex;
EGG::Heap *EGG::Heap::sCurrentHeap;
BOOL EGG::Heap::sIsHeapListInitialized;
EGG::Heap *EGG::Heap::sAllocatableHeap;
void (*EGG::Heap::sErrorCallback)(const EGG::HeapErrorArg &arg);
void (*EGG::Heap::sAllocCallback)(const EGG::HeapAllocArg &arg);
void *EGG::Heap::sErrorCallbackArg;
void *EGG::Heap::sAllocCallbackArg;
EGG::Thread *EGG::Heap::sAllocatableThread;
