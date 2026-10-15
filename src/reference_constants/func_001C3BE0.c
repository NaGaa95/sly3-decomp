// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Key { int first,second; }; extern struct Key D_00323688; void func_001C21F0(void *,int); void func_001C2E58(void *,struct Key); void func_001C3BE0(void *p) { func_001C21F0(p,6); func_001C2E58(p,D_00323688); }
