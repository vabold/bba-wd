#pragma once

#include <Common.h>

extern "C" {
typedef struct {
    u8 _00[0x18 - 0x00];
} OSMutex;

void OSInitMutex(OSMutex *mutex);
void OSLockMutex(OSMutex *mutex);
void OSUnlockMutex(OSMutex *mutex);
}