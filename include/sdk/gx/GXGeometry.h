#ifndef GX_GEOMETRY_H
#define GX_GEOMETRY_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXBegin(GXPrimitive prim, GXVtxFmt vtxFmt, u16 nVerts);
static void GXEnd(void) {}
void GXSetCullMode(GXCullMode mode);

#ifdef __cplusplus
}
#endif

#endif
