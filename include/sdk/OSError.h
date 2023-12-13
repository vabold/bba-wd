#ifndef OS_ERROR_H
#define OS_ERROR_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void OSReport(const char *fmt, ...);
void OSPanic(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
