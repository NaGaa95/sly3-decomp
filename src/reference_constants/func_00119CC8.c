// Reference algorithm: src/hand/func_001D00D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_002B9EA8(void *,int,qword); void func_002B9D98(void *,int,qword); void func_00119CC8(void *p,int value,qword vector) { if(value != 0x7FFFFFFF) func_002B9EA8(p, value, vector); else func_002B9D98(p, 0, vector); }
