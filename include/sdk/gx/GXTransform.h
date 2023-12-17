#ifndef GX_TRANSFORM_H
#define GX_TRANSFORM_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetViewport(f32 left, f32 up, f32 width, f32 height, f32, f32);
void GXSetScissor(u32 left, u32 up, u32 width, u32 height);
void GXSetScissorBoxOffset(u32, u32);

#ifdef __cplusplus
}
#endif

#endif
