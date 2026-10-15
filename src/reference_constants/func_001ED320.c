// Reference algorithm: src/hand/func_0012F8C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); int func_001ED170(void *,qword,int); int func_001ED1F0(void *,qword,int); int func_001ED320(void *p,qword vector,int enabled) { if(enabled) return func_001ED1F0(p, vector, 0); return func_001ED170(p, vector, 0); }
