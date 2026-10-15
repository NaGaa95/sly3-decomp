// Reference algorithm: src/hand/func_001C3E90.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern int D_004797C8; extern char D_00468D30[]; extern char D_0036BD20[]; void func_0021D360(void *); void func_00171A58(void *); void func_00184A60(void) { if (D_004797C8 & 0x10) func_0021D360(D_00468D30); func_00171A58(D_0036BD20); }
