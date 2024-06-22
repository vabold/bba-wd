#ifndef GX_PIXEL_H
#define GX_PIXEL_H

#include <sdk/gx/GXTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
        GXLogicOp op);
void GXSetColorUpdate(GXBool enable);
void GXSetAlphaUpdate(GXBool enable);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);

#ifdef __cplusplus
}
#endif

#endif
