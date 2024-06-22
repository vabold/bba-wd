#ifndef GX_TEV_H
#define GV_TEV_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetNumTevStages(u8 nStages);

#ifdef __cplusplus
}
#endif

#endif
