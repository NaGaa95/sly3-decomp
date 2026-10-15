// Sly 2 reference: src/hand/func_00133448.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int id; int cref; struct E *pnext; };
struct S { int pad[2]; struct E *pfirst; };
extern char D_004798D0[];
void func_0011E1F0(void *, void *);
void func_0013BD88(struct S *p, int id) {
    struct E **ppe;
    struct E *pe;
    for (ppe = &p->pfirst; (pe = *ppe) != 0; ppe = &pe->pnext) { if (pe->id == id) { if (--pe->cref <= 0) { *ppe = pe->pnext; func_0011E1F0(D_004798D0, pe); } break; } }
}
