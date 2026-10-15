// Reference algorithm: src/hand/func_001D00D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_002B9968(void *,int,int,void *,void *,int); void func_002B9700(void *,int,int,void *,void *,int); void func_00119C58(void *p,int value,int count,void *points,void *output,int flags) { if(value != 0x7FFFFFFF) func_002B9968(p, value, count, points, output, flags); else func_002B9700(p, 0, count, points, output, flags); }
