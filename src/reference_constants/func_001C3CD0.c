// Reference algorithm: src/hand/func_001C2D70.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F43C8(void *); void func_001C21F0(void *,int); void func_001C3CD0(char *p) { if(func_001F43C8(*(void **)p)>0)func_001C21F0(p,7); else func_001C21F0(p,9); }
