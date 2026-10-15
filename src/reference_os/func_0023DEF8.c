// Sly 2 reference: src/hand/func_001F4DA8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct N { int pad[2]; void *p8; char pad2[0xAC - 0xC]; struct N *next; };
struct G;
extern struct G D_00475480;
void func_0023E228(void *);
void func_001CBAA0(struct G *, struct N *);
void func_0023DEF8(void *pa, void *pb, struct N **ppn)
{
    struct N *pfree = 0;
    struct N *pn;
loop:
    pn = *ppn;
    if (pn) {
        int i = pn->p8 == pa;
        if (((struct N *)((char *)pn + (i << 6)))->p8 == pb) {
            *ppn = pn->next;
            pn->next = pfree;
            pfree = pn;
        } else {
            ppn = &pn->next;
        }
        goto loop;
    }
    if (pfree) {
        func_0023E228(pa);
        func_001CBAA0(&D_00475480, pfree);
    }
}
