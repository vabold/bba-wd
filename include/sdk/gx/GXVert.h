#ifndef GX_VERT_H
#define GX_VERT_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile union {
    // 1-byte
    char c;
    unsigned char uc;
    // 2-byte
    short s;
    unsigned short us;
    // 4-byte
    int i;
    unsigned int ui;
    void *p;
    float f;
} WGPIPE : 0xCC008000;

static inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    WGPIPE.f = x;
    WGPIPE.f = y;
    WGPIPE.f = z;
}

#ifdef __cplusplus
}
#endif

#endif
