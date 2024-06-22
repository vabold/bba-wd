#ifndef GX_TRANSFORM_H
#define GX_TRANSFORM_H

#include <sdk/gx/GXTypes.h>

#include <sdk/mtx/mtx.h>
#include <sdk/mtx/mtx44.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetProjection(const Mtx44 mtx, GXProjectionType type);
void GXLoadPosMtxImm(const Mtx, u32 id);
void GXSetCurrentMtx(u32 id);
void GXSetViewport(f32 left, f32 up, f32 width, f32 height, f32 near, f32 far);
void GXSetScissor(u32 left, u32 up, u32 width, u32 height);
void GXSetScissorBoxOffset(u32 x, u32 y);

#ifdef __cplusplus
}
#endif

#endif
