// Reference algorithm: src/hand/func_00221120.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
float func_001EF588(char *p) { int index = *(int *)(p + 0x30) - 1; p += index * 4; return *(float *)(p + 0x240); }
