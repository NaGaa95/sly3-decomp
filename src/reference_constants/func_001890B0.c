// Reference algorithm: src/hand/func_001FB060.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "relationship_lifecycle_api.h"
extern char D_0036C6E8[];
/* The legacy generic queue stores these 32-bit kind-specific payload words;
its pointer view is a bit carrier, not a dereferenced mode/option pointer. */ void func_00189240(void *, void *, int, void *, void *);
void func_001890B0(void *receiver, int mode, int option) {
    func_00189240(D_0036C6E8, receiver, 1, (void *)mode, (void *)option);
}
