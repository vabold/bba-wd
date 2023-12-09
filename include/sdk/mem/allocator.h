#ifndef MEM_ALLOCATOR_H
#define MEM_ALLOCATOR_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _00[0x10 - 0x00];
} MEMAllocator;

#ifdef __cplusplus
}
#endif

#endif
