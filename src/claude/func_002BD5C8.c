// Reference: Sly 2 src/hand/func_00259170.c; target Sly 3 0x002BD5C8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct { int cb; int cbAlign; } AREQ;
typedef struct {
    int x0; int x4; void *x8; int pad0C; int x10; int pad14[3]; int x20; int pad24[3]; int x30;
    char p34[0xCC - 0x34]; int xCC; int xD0; int xD4;
} X;
typedef struct { char p0[0xD4]; X *px; } SO;
extern char D_00475480[];
extern char D_003573C0[];
void func_001C7DC8(SO *p);
void *memset(void *p, int c, int n);
int memcmp(const void *a, const void *b, int n);
void *func_0017E1B8(void *pg, int kind, int oid, SO *p);
void func_002BD548(SO *p, int f);
void *func_001D24D0(AREQ *preq, void *pv);
void func_002BD5C8(SO *p)
{
    void *a[4];
    AREQ req;
    AREQ *preq;
    X *x;
    int o1;
    int o2 = -1;

    func_001C7DC8(p);
    {
        X *x0 = p->px;
        o1 = x0->x20;
        if (x0->x10 == 2)
            o2 = x0->x30;
    }
    memset(a, 0, 0x10);
    if (o1 != -1)
        a[0] = func_0017E1B8(D_00475480, 4, o1, p);
    if (o2 != -1) {
        void *q = func_0017E1B8(D_00475480, 4, o2, p);
        a[0] = 0;
        a[1] = q;
    }
    x = p->px;
    switch (x->x4) {
    case 1: {
        int cc = x->xCC;
        int d0 = x->xD0;
        if (cc != -1)
            a[2] = func_0017E1B8(D_00475480, 4, cc, p);
        if (d0 != -1)
            a[3] = func_0017E1B8(D_00475480, 4, d0, p);
        break;
    }
    case 0:
        if (x->xD4 != -1)
            a[2] = func_0017E1B8(D_00475480, 4, x->xD4, p);
        break;
    }
    if (p->px->x8 == 0)
        p->px->x8 = D_003573C0;
    if (memcmp(p->px->x8, a, 0x10)) {
        func_002BD548(p, 1);
        preq = &req;
        req.cb = 0x10;
        preq->cbAlign = 0x10;
        p->px->x8 = func_001D24D0(preq, a);
    }
}
