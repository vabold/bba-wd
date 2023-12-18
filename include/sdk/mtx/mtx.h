#ifndef MTX_MTX_H
#define MTX_MTX_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];

void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXInverse(const Mtx, Mtx);
void PSMTXInvXpose(const Mtx, Mtx);

#ifdef __cplusplus
}
#endif

#endif