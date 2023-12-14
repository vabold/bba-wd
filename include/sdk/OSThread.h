#ifndef OS_THREAD_H
#define OS_THREAD_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _000[0x304 - 0x000];
    u8 *stackBase;
    u32 *stackEnd;
    u8 _30c[0x318 - 0x30c];
} OSThread;

void *OSSetSwitchThreadCallback(void *callback);
OSThread *OSGetCurrentThread();
BOOL OSIsThreadTerminated(OSThread *thread);
BOOL OSCreateThread(OSThread *thread, void *callback, void *param, void *stack, u32 stackSize,
        s32 priority, u16 attr);
void OSCancelThread(OSThread *thread);
void OSDetachThread(OSThread *thread);

#ifdef __cplusplus
}
#endif

#endif
