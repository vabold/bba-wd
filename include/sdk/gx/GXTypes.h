#ifndef GX_TYPES_H
#define GX_TYPES_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _GXAttnFn {
    GX_AF_SPEC,
    GX_AF_SPOT,
    GX_AF_NONE,
} GXAttnFn;

typedef enum _GXAttr {
    GX_VA_PNMTXIDX,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NRM,
    GX_VA_CLR0,
    GX_VA_CLR1,
    GX_VA_TEX0,
    GX_VA_TEX1,
    GX_VA_TEX2,
    GX_VA_TEX3,
    GX_VA_TEX4,
    GX_VA_TEX5,
    GX_VA_TEX6,
    GX_VA_TEX7,
    GX_POS_MTX_ARRAY,
    GX_NRM_MTX_ARRAY,
    GX_TEX_MTX_ARRAY,
    GX_LIGHT_ARRAY,
    GX_VA_NBT,
    GX_VA_MAX_ATTR,
    GX_VA_NULL = 255,
} GXAttr;

typedef enum _GXAttrType {
    GX_NONE,
    GX_DIRECT,
    GX_INDEX8,
    GX_INDEX16,
} GXAttrType;

typedef enum _GXBlendFactor {
    GX_BL_ZERO,
    GX_BL_ONE,
    GX_BL_SRCCLR,
    GX_BL_INVSRCCLR,
    GX_BL_SRCALPHA,
    GX_BL_INVSRCALPHA,
    GX_BL_DSTALPHA,
    GX_BL_INVDSTALPHA,
    GX_BL_DSTCLR = GX_BL_SRCCLR,
    GX_BL_INVDSTCLR = GX_BL_INVSRCCLR,
} GXBlendFactor;

typedef enum _GXBlendMode {
    GX_BM_NONE,
    GX_BM_BLEND,
    GX_BM_LOGIC,
    GX_BM_SUBTRACT,
    GX_MAX_BLENDMODE,
} GXBlendMode;

typedef u8 GXBool;
#define GX_TRUE ((GXBool)TRUE)
#define GX_FALSE ((GXBool)FALSE)
#define GX_ENABLE GX_TRUE
#define GX_DISABLE GX_FALSE

typedef enum _GXChannelID {
    GX_COLOR0,
    GX_COLOR1,
    GX_ALPHA0,
    GX_ALPHA1,
    GX_COLOR0A0,
    GX_COLOR1A1,
    GX_COLOR_ZERO,
    GX_ALPHA_BUMP,
    GX_ALPHA_BUMPN,
    GX_COLOR_NULL = 255,
} GXChannelID;

typedef struct _GXColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;

typedef enum _GXColorSrc {
    GX_SRC_REG,
    GX_SRC_VTX,
} GXColorSrc;

typedef enum _GXCompare {
    GX_NEVER,
    GX_LESS,
    GX_EQUAL,
    GX_LEQUAL,
    GX_GREATER,
    GX_NEQUAL,
    GX_GEQUAL,
    GX_ALWAYS,
} GXCompare;

typedef enum _GXCompCnt {
    GX_POS_XY = 0,
    GX_POS_XYZ,

    GX_NRM_XYZ = 0,
    GX_NRM_NBT,
    GX_NRM_NBT3,

    GX_CLR_RGB = 0,
    GX_CLR_RGBA,

    GX_TEX_S = 0,
    GX_TEX_ST,
} GXCompCnt;

typedef enum _GXCompType {
    GX_U8 = 0,
    GX_S8,
    GX_U16,
    GX_S16,
    GX_F32,

    GX_RGB565 = 0,
    GX_RGB8,
    GX_RGBX8,
    GX_RGBA4,
    GX_RGBA6,
    GX_RGBA8,
} GXCompType;

typedef enum _GXCullMode {
    GX_CULL_NONE,
    GX_CULL_FRONT,
    GX_CULL_BACK,
    GX_CULL_ALL,
} GXCullMode;

typedef enum _GXDiffuseFn {
    GX_DF_NONE,
    GX_DF_SIGN,
    GX_DF_CLAMP,
} GXDiffuseFn;

typedef enum _GXLightID {
    GX_LIGHT0 = (1 << 0),
    GX_LIGHT1 = (1 << 1),
    GX_LIGHT2 = (1 << 2),
    GX_LIGHT3 = (1 << 3),
    GX_LIGHT4 = (1 << 4),
    GX_LIGHT5 = (1 << 5),
    GX_LIGHT6 = (1 << 6),
    GX_LIGHT7 = (1 << 7),
    GX_MAX_LIGHT = (1 << 8),
    GX_LIGHT_NULL = 0,
} GXLightID;

typedef enum _GXLogicOp {
    GX_LO_CLEAR,
    GX_LO_AND,
    GX_LO_REVAND,
    GX_LO_COPY,
    GX_LO_INVAND,
    GX_LO_NOOP,
    GX_LO_XOR,
    GX_LO_OR,
    GX_LO_NOR,
    GX_LO_EQUIV,
    GX_LO_INV,
    GX_LO_REVOR,
    GX_LO_INVCOPY,
    GX_LO_INVOR,
    GX_LO_NAND,
    GX_LO_SET,
} GXLogicOp;

typedef enum _GXPosNrmMtx {
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27,
} GXPosNrmMtx;

typedef enum _GXPrimitive {
    GX_POINTS = 0xB8,
    GX_LINES = 0xA8,
    GX_LINESTRIP = 0xB0,
    GX_TRIANGLES = 0x90,
    GX_TRIANGLESTRIP = 0x98,
    GX_TRIANGLEFAN = 0xA0,
    GX_QUADS = 0x80,
} GXPrimitive;

typedef enum _GXProjectionType {
    GX_PERSPECTIVE,
    GX_ORTHOGRAPHIC,
} GXProjectionType;

typedef enum _GXTexCoordID {
    GX_TEXCOORD0,
    GX_TEXCOORD1,
    GX_TEXCOORD2,
    GX_TEXCOORD3,
    GX_TEXCOORD4,
    GX_TEXCOORD5,
    GX_TEXCOORD6,
    GX_TEXCOORD7,
    GX_MAX_TEXCOORD,
    GX_TEXCOORD_NULL = 255,
} GXTexCoordID;

typedef enum _GXTexMapID {
    GX_TEXMAP0,
    GX_TEXMAP1,
    GX_TEXMAP2,
    GX_TEXMAP3,
    GX_TEXMAP4,
    GX_TEXMAP5,
    GX_TEXMAP6,
    GX_TEXMAP7,
    GX_MAX_TEXMAP,
    GX_TEXMAP_NULL = 255,
    GX_TEX_DISABLE,
} GXTexMapID;

typedef enum _GXTevMode {
    GX_MODULATE,
    GX_DECAL,
    GX_BLEND,
    GX_REPLACE,
    GX_PASSCLR,
} GXTevMode;

typedef enum _GXTevStageID {
    GX_TEVSTAGE0,
    GX_TEVSTAGE1,
    GX_TEVSTAGE2,
    GX_TEVSTAGE3,
    GX_TEVSTAGE4,
    GX_TEVSTAGE5,
    GX_TEVSTAGE6,
    GX_TEVSTAGE7,
    GX_TEVSTAGE8,
    GX_TEVSTAGE9,
    GX_TEVSTAGE10,
    GX_TEVSTAGE11,
    GX_TEVSTAGE12,
    GX_TEVSTAGE13,
    GX_TEVSTAGE14,
    GX_TEVSTAGE15,
    GX_MAX_TEVSTAGE,
} GXTevStageID;

typedef enum _GXVtxFmt {
    GX_VTXFMT0,
    GX_VTXFMT1,
    GX_VTXFMT2,
    GX_VTXFMT3,
    GX_VTXFMT4,
    GX_VTXFMT5,
    GX_VTXFMT6,
    GX_VTXFMT7,
    GX_MAX_VTXFMT,
} GXVtxFmt;

#ifdef __cplusplus
}
#endif

#endif
