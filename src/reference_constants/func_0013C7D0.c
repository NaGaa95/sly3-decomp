// Reference algorithm: src/hand/func_00133E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X;
struct E { int f0; struct X *px; float *pg; };
struct P { char pad[0x4468]; int fDirty; int c; struct E *aae[3]; };
void func_0013C388(struct P *, struct X *, struct X *, int);
void *func_00291F38(void *, void *, unsigned int);
void func_0013C7D0(struct P *p)
{
    int i;
    if (!p->fDirty)
        return;
    p->fDirty = 0;
    if (!p->c)
        return;
    for (i = 0; i < 3; i++) {
        struct E *pe = p->aae[i];
        struct E *ae = pe;
        float gMax = *pe->pg;
        int j;
        for (j = p->c, pe++; --j > 0; pe++) {
            float g = *pe->pg;
            if (gMax <= g) {
                gMax = g;
            } else {
                struct E *pe2;
                struct E e;
                for (pe2 = pe - 1; pe2 >= ae; pe2--) {
                    if (*pe2->pg <= g)
                        break;
                    if (pe->f0 != pe2->f0)
                        func_0013C388(p, pe->px, pe2->px, 0);
                }
                pe2++;
                e = *pe;
                func_00291F38(pe2 + 1, pe2, (pe - pe2) * sizeof(struct E));
                *pe2 = e;
            }
        }
    }
}
