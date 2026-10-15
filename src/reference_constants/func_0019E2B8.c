// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct MSG {
    int cb;
    int nKind;
};
struct Q {
    char pad[0x20];
    struct E *pr;
    int n;
};
struct E {
    int oid;
    int c;
    int x8;
    int xc;
    char dl[0xC];
    int x1c;
    float g;
    void *pv;
    int x28;
    float h;
};
struct R {
    int a;
    void *p;
    int x8;
    int padC;
    int n;
    int pad14;
    unsigned long fl;
    char pad[0xB0];
};
struct S {
    char pad[0x28];
    union {
        unsigned long fl;
        struct {
            unsigned char unused[7];
            unsigned char last;
        }
        flags;
    };
    char p0[0x20];
    int x60;
    char p1[0x7C];
    int ce0;
    struct R *ar;
    char p2[0x11C];
    int c;
    struct E ae[4];
};
extern char D_00475480[];
void *func_0017E1B8(void *g, int n, int oid, struct S *p);
void func_0011AF38(void *pdl, int ib);
void *func_001D2538(struct MSG *pmsg);
void func_0011AF60(void *pdl, void *pv);
void func_001F3BF8(struct S *p);
void func_0023B9C8(struct S *p);
void func_0019E2B8(struct S *p) {
    int i, j;
    struct E *pe;
    struct R *pr;
    for (i = 0; i < p->c; i++) {
        pe = &p->ae[i];
        pe->pv = func_0017E1B8(D_00475480, 4, pe->oid, p);
        if (!pe->pv) {
            i--;
            p->c--;
            continue;
        }
        func_0011AF38(pe->dl, 0x60);
        for (j = 0; j < pe->c; j++) {
            struct MSG msg;
            struct Q *q;
            msg.cb = 0x70;
            msg.nKind = 0x10;
            q = (struct Q *)func_001D2538(&msg);
            q->pr = pe;
            q->n = -1;
            func_0011AF60(pe->dl, q);
        }
    }
    func_001F3BF8(p);
    pr = &p->ar[p->ce0++];
    pr->a = p->x60;
    pr->n = -1;
    pr->p = p;
    pr->fl |= 1UL << 16;
    pr->fl |= 1UL << 17;
    if ((int)(p->fl >> 56) & 1) func_0023B9C8(p);
}
