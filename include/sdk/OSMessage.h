#ifndef OS_MESSAGE_H
#define OS_MESSAGE_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _00[0x20 - 0x00];
} OSMessageQueue;

void OSInitMessageQueue(OSMessageQueue *queue, void *msgArray, s32 msgCount);

#ifdef __cplusplus
}
#endif

#endif
