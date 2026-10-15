// Reference algorithm: src/hand/func_001F0128.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { int a, b, c; };
struct P { char pad[0x64]; struct T *pt; };
struct CB { int cb; int n; };
struct T *func_001D2470(struct CB *);
void func_00239778(struct P *p, int a, int b, int c)
{
    struct CB cb;
    struct T *pt;
    cb.cb = 0xC; cb.n = 0x10;
    pt = func_001D2470(&cb);
    p->pt = pt;
    pt->a = a; pt->b = b; pt->c = c;
}
