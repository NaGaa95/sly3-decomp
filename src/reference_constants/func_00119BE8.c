// Reference algorithm: src/hand/func_001D00D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_002B8E08(void *,int,qword,qword,void *,int); void func_002B89F8(void *,int,qword,qword,void *,int); void func_00119BE8(void *p,int value,qword origin,qword direction,void *output,int flags) { if(value != 0x7FFFFFFF) func_002B8E08(p, value, origin, direction, output, flags); else func_002B89F8(p, 0, origin, direction, output, flags); }
