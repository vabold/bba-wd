#ifndef OS_MUTEX_H
#define OS_MUTEX_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _00[0x18 - 0x00];
} OSMutex;

void OSInitMutex(OSMutex *mutex);
void OSLockMutex(OSMutex *mutex);
void OSUnlockMutex(OSMutex *mutex);

#ifdef __cplusplus
}
#endif

#endif
