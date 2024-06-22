#ifndef GX_LIGHT_H
#define GX_LIGHT_H

#include <sdk/gx/GXTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetChanMatColor(GXChannelID chan, GXColor matColor);
void GXSetNumChans(u8 nChans);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc ambSrc, GXColorSrc matSrc,
        GXLightID lightMask, GXDiffuseFn diffFn, GXAttnFn attnFn);

#ifdef __cplusplus
}
#endif

#endif
