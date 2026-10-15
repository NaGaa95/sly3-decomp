#ifndef SLY3_M2C_PRELUDE_H
#define SLY3_M2C_PRELUDE_H
/* Fixed-width aliases for the historical EE compiler's data model. */
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef float f32;
typedef double f64;
#ifndef NULL
#define NULL 0
#endif
/* The pinned upstream m2c package provides the draft-only access macros. */
#include "m2c_macros.h"
#endif
