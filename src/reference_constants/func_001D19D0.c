// Reference algorithm: src/hand/func_001AD740.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int x0, x4; void *x8; int xc, x10; char *x14; int x18; };
struct G { int pad[14]; int x24; };
extern struct E D_0046F570[];
extern struct G D_0046F550;
extern int D_00375228;
struct S { int x0, x4; char *x8; };
void func_001D3A90(struct G *g);
int func_001D4658(struct G *g);
void func_00262450(void *a, char *b);
void func_001D19D0(struct S *s)
{
    struct E *e;
    if (D_00375228 != 1) {
        func_001D3A90(&D_0046F550);
        return;
    }
    if (!func_001D4658(&D_0046F550))
        return;
    e = &D_0046F570[D_0046F550.x24];
    if (e->x14 == s->x8)
        func_00262450(e->x8, s->x8 + 0x699);
    else
        func_00262450(e->x8, s->x8 + 0x696);
}
