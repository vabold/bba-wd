#ifndef MTX_MTX_H
#define MTX_MTX_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];

void PSMTXIdentity(Mtx m);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXInvXpose(const Mtx src, Mtx invX);

#ifdef __cplusplus
}
#endif

#endif
