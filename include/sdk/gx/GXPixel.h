#ifndef GX_PIXEL_H
#define GX_PIXEL_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetBlendMode(int, int, int, int);
void GXSetColorUpdate(int);
void GXSetAlphaUpdate(int);
void GXSetZMode(int, int, int);

#ifdef __cplusplus
}
#endif

#endif
