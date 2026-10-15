// Reference algorithm: src/hand/func_0015E380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a, b, c; };
struct E *func_0017DBE8(char *p, int i)
{
    return &((struct E *)(p + 0x1820))[(i * 0x95675) & 0x1FF];
}
