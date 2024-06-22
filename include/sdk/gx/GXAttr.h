#ifndef GX_ATTR_H
#define GX_ATTR_H

#include <sdk/gx/GXTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmt(GXVtxFmt vtxFmt, GXAttr attr, GXCompCnt compCnt, GXCompType compType,
        u8 shift);
void GXInvalidateVtxCache(void);
void GXSetNumTexGens(u8 nStages);

#ifdef __cplusplus
}
#endif

#endif
