// Reference algorithm: src/hand/func_001F6838.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct T { char pad[0x70]; ulong fl; };
struct S { char pad[0xDC]; struct T *pt; };
int func_0023FC68(struct S *p) { if (!p->pt) return 1; return (int)((long)(p->pt->fl << 30) >> 32) & 1; }
