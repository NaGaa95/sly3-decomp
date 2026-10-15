// Reference algorithm: src/hand/func_0012F8C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Context { char data[0x11C0]; }; extern struct Context D_0036E740[]; void func_001F4B38(void *,void *); void func_001F4B00(void *unused,int index,void *p) { func_001F4B38(D_0036E740 + index, p); }
