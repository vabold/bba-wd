#ifndef MTX_MTX44_H
#define MTX_MTX44_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx44[4][4];

void C_MTXOrtho(Mtx44 *m, f32, f32, f32, f32, f32, f32);

#ifdef __cplusplus
}
#endif

#endif
