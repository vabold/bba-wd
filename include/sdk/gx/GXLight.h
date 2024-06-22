#ifndef GX_LIGHT_H
#define GX_LIGHT_H

#include <sdk/GXTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetChanMatColor(int, _GXColor color);
void GXSetNumChans(int nChans);
void GXSetChanCtrl(int, int, int, int, int, int, int);

#ifdef __cplusplus
}
#endif

#endif
