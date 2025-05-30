#ifndef GX_ATTR_H
#define GX_ATTR_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetVtxDesc(int name, int type);
void GXClearVtxDesc();
void GXSetVtxAttrFmt(int, int, int, int, int);
void GXInvalidateVtxCache();
void GXSetNumTexGens(int);

#ifdef __cplusplus
}
#endif

#endif
