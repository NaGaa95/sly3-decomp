// Reference algorithm: src/hand/func_00129558.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CRef { short tag,reserved; float value; }; extern char D_0036BD20[]; float func_00171C98(void *); struct CRef *func_00125AF8(struct CRef *p) { p->value = func_00171C98(D_0036BD20); p->tag = 0x14; return p; }
