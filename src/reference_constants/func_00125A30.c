// Reference algorithm: src/hand/func_00182E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CRef { short tag; short padding; int value; }; int func_0025E150(void); struct CRef *func_00125A30(struct CRef *p) { p->value = func_0025E150(); p->tag = 0x13; return p; }
