#pragma once

#include <egg/core/eggDisposer.h>
#include <sdk/OSMutex.h>
#include <sdk/mem/heapCommon.h>

namespace EGG {

class Allocator;
class ExpHeap;
class Thread;

struct HeapErrorArg {
    const char *name;
    void *arg;
};

struct HeapAllocArg {
    HeapAllocArg() {
        arg = NULL;
        size = 0;
        align = 0;
        heap = NULL;
    }

    void *arg;
    u32 size;
    int align;
    Heap *heap;
};

class Heap : Disposer {
public:
    enum eHeapKind {
        HEAP_KIND_NONE,
        HEAP_KIND_EXPANDED,
        HEAP_KIND_FRAME,
        HEAP_KIND_UNIT,
        HEAP_KIND_ASSERT
    };

    Heap(MEMiHeapHead *handle);

    virtual ~Heap();
    virtual eHeapKind getHeapKind() const = 0;
    virtual void initAllocator(Allocator *allocator, s32 align) = 0;
    virtual void *alloc(size_t size, s32 align) = 0;
    virtual void free(void *block) = 0;
    virtual void destroy() = 0;
    virtual void vf_20() = 0;
    virtual s32 getAllocatableSize(s32 align) = 0;
    virtual void vf_28() = 0;
    virtual void vf_2c() = 0;

    Heap *findParentHeap();
    void dispose();
    void dump();
    Heap *becomeCurrentHeap();
    Heap *_becomeCurrentHeapWithoutLock();

    bool tstDisableAllocation() {
        return hasFlag(0);
    }

    void enableAllocation() {
        clearFlag(0);
    }

    void disableAllocation() {
        setFlag(0);
    }

    void appendDisposer(Disposer *disposer) {
        nw4r::ut::List_Append(&mChildren, disposer);
    }

    void removeDisposer(Disposer *disposer) {
        nw4r::ut::List_Remove(&mChildren, disposer);
    }

    void *getStartAddress() {
        return this;
    }

    void *getEndAddress() {
        return MEMGetHeapEndAddress(mHeapHandle);
    }

    const char *getName() {
        return mName;
    }

    static void initialize();
    static void *alloc(size_t size, int align, Heap *heap);
    static Heap *findHeap(MEMiHeapHead *handle);
    static Heap *findContainHeap(const void *memBlock);
    static void free(void *block, Heap *heap);
    static void dumpAll();

    static ExpHeap *dynamicCastToExp(Heap *heap) {
        if (heap->getHeapKind() == HEAP_KIND_EXPANDED) {
            return reinterpret_cast<ExpHeap *>(heap);
        }

        return NULL;
    }

    static Heap *getCurrentHeap() {
        return sCurrentHeap;
    }

    static nw4r::ut::List *getHeapList() {
        return &sHeapList;
    }

private:
    // HACK: Avoid defining TBitFlag for now
    bool hasFlag(u8 idx) volatile {
        return mFlags & 1 << idx;
    }

    // HACK: Avoid defining TBitFlag for now
    void setFlag(u8 idx) volatile {
        mFlags |= (1 << idx);
    }

    // HACK: Avoid defining TBitFlag for now
    void clearFlag(u8 idx) volatile {
        mFlags &= ~(1 << idx);
    }

    MEMiHeapHead *mHeapHandle;
    u32 _14;
    Heap *mParentHeap;
    u16 mFlags;
    u8 _1e[0x28 - 0x1e];
    nw4r::ut::List mChildren;
    const char *mName;

    static nw4r::ut::List sHeapList;
    static OSMutex sRootMutex;

    static Heap *sCurrentHeap;
    static BOOL sIsHeapListInitialized;
    static Heap *sAllocatableHeap;
    static void (*sErrorCallback)(const HeapErrorArg &arg);
    static void (*sAllocCallback)(const HeapAllocArg &arg);
    static void *sErrorCallbackArg;
    static void *sAllocCallbackArg;
    static Thread *sAllocatableThread;
};

} // namespace EGG

void *operator new(size_t size);
void *operator new(size_t size, int align);
void *operator new(size_t size, EGG::Heap *heap, int align);
void *operator new[](size_t size);
void *operator new[](size_t size, int align);
void *operator new[](size_t size, EGG::Heap *heap, int align);
void operator delete(void *block);
void operator delete[](void *block);
