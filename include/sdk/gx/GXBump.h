#ifndef GX_BUMP_H
#define GX_BUMP_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetNumIndStages(u8 nStages);
void __GXSetIndirectMask(u32 mask);

#ifdef __cplusplus
}
#endif

#endif
