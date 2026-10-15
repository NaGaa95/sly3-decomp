// Reference algorithm: src/hand/func_001D00D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_002B9478(void *,int,qword,void *,int,float); void func_002B9230(void *,int,qword,void *,int,float); void func_00119C20(void *p,int value,qword vector,void *output,int flags,float limit) { if(value != 0x7FFFFFFF) func_002B9478(p, value, vector, output, flags, limit); else func_002B9230(p, 0, vector, output, flags, limit); }
