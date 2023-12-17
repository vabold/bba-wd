#ifndef GX_FRAMEBUF_H
#define GX_FRAMEBUF_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _00[0x04 - 0x00];
    u16 fbWidth;
    u16 efbHeight;
} _GXRenderModeObj;

#ifdef __cplusplus
}
#endif

#endif
