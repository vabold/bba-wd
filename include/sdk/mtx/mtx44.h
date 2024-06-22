#ifndef MTX_MTX44_H
#define MTX_MTX44_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx44[4][4];

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#ifdef __cplusplus
}
#endif

#endif
