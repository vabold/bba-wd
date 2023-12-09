#ifndef OS_THREAD_H
#define OS_THREAD_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
} OSThread;

OSThread *OSGetCurrentThread();

#ifdef __cplusplus
}
#endif

#endif
