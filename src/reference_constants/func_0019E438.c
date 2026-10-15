// Reference algorithm: src/hand/func_001819E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct DLE { void *next; void *prev; };
struct R { char pad[0x10]; char dl[0xC]; };
struct Q { char pad[0x20]; struct R *pr; char p1[0x3C]; struct DLE dle; };
struct E { int a; int b; int c; int d; char p[0xC]; int x1c; float g; int x24; int x28; float h; };
struct S { char pad[0x1F4]; int c; struct E ae[4]; struct Q *pqFirst; };
void func_0019B668(struct S *p);
void func_0011AF50(struct DLE *pdle);
void func_0011AF60(void *pdl, void *pv);
void func_0011AF40(void *pdl);
void func_0019E4F8(struct S *p, struct E *pe);
void func_0019E438(struct S *p)
{
    struct Q *q;
    int i;
    func_0019B668(p);
    q = p->pqFirst;
    while (q) {
        struct Q *qNext = (struct Q *)q->dle.next;
        func_0011AF50(&q->dle);
        func_0011AF60(q->pr->dl, q);
        q = qNext;
    }
    func_0011AF40(&p->pqFirst);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->d = pe->b;
        func_0019E4F8(p, pe);
    }
}
