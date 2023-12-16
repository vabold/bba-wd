#ifndef COMMON_H
#define COMMON_H

#ifndef NULL
#define NULL 0
#endif

#ifndef FLT_MAX
#define FLT_MAX 3.4028235e+38f
#endif

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef float f64;

typedef u32 size_t;

typedef int BOOL;
enum { FALSE, TRUE };

#define ROUND_UP(num, align) (((u32)(num) + (align) - 1) & (~(align) + 1))
#define ROUND_DOWN(num, align) ((u32)(num) & (~(align) + 1))
#define PTR_SIZE(start, end) (u32)((u32)(end) - (u32)(start))

#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *ptr, int value, size_t num);

#ifdef __cplusplus
}
#endif

#endif
