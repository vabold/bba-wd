#ifndef GX_VERT_H
#define GX_VERT_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    volatile f32 *pipe = (f32 *)(0xcc008000);
    *pipe = x;
    *pipe = y;
    *pipe = z;
}

#ifdef __cplusplus
}
#endif

#endif
