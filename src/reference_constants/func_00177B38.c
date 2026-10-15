// Reference algorithm: src/hand/func_001904E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001C7D60(void *);
#include "owner_parent_link.h"
void func_00177B38(char *p) { void *owner = **(void ***)(*(char **)(p + 0xD4) + 8); void *result = func_001C7D60(owner); func_001C7A00(p, result, 0); }
