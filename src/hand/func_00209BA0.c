// Collect objects with flag 8 whose owner identifier differs, and reset their embedded resource.
// Reference algorithm: src/hand/func_001CD9E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct LO { char pad[0x3C]; int x40; char pad2[0x70 - 0x40]; char x80[0x4C]; int xCC; };
struct G { char pad[0x44F8]; int x3D5C; };
int func_0017E208(struct G *p, int a, int b, int c, int d, struct LO **ap);
void func_0018E0B8(void *p);
static inline int FPtr(int v) { return !(v & 1); }
static inline int Flags(struct LO *plo)
{
    int v = plo->x40;
    if (FPtr(v)) v = *(int *)v;
    return v;
}
void func_00209BA0(struct G *p)
{
    struct LO *ap[0x400];
    int n, i;
    n = func_0017E208(p, 0x105, 0x2F, 0, 0x400, ap);
    for (i = 0; i < n; i++) {
        struct LO *plo = ap[i];
        if ((Flags(plo) & 8) && plo->xCC != p->x3D5C) func_0018E0B8(plo->x80);
    }
}
