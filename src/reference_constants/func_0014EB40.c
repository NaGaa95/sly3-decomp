// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct I {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
};
struct A {
    char pad[0x138];
    struct I *pi;
    void *p15C;
    void *p160;
};
struct Q {
    char pad[0x127C];
    struct A *pa;
};
struct P {
    char pad[0x198];
    int x188;
    int x18C;
    int x190;
    struct A *pa;
};
extern int D_004794C4;
extern char D_0046F770[];
extern char D_0036C700[];
int func_0013B500(struct Q *q, int k);
void func_0021E870(void *pv, int n, float g);
void *func_002459F8(int n);
void func_00244F08(void *pv, int n);
void func_001854C8(void *pv, int n, struct P *p);
void func_00155F80(struct Q *q, int n, struct P *p);
void func_0014DC98(struct A *pa, int n);
void func_001A20F8(struct P *p, struct Q *q);
void func_0014EB40(struct P *p, struct Q *q) {
    struct A *pqa, *ppa;
    if (!func_0013B500(q, 0x33)) return;
    pqa = q->pa;
    if (!pqa && !p->pa) return;
    ppa = p->pa;
    if (ppa && D_004794C4 && !ppa->pi->x10) {
        func_0021E870(D_0046F770, 0x1E5, 15.0f);
        func_00244F08(func_002459F8(0x36), 0);
        return;
    }
    if (p->x190 || (pqa && pqa->pi->x14 != p->x188)) {
        func_001854C8(D_0036C700, 0x45, p);
        return;
    }
    if (p->pa) func_00244F08(func_002459F8(0x27), 0);
    func_00155F80(q, 0, p);
    if (q->pa && p->pa) {
        q->pa->p15C = p;
        func_0014DC98(q->pa, 3);
        p->pa->p160 = q;
        func_0014DC98(p->pa, 2);
    }
    else if (q->pa) {
        q->pa->p15C = p;
        func_0014DC98(q->pa, 3);
    }
    else {
        p->pa->p160 = q;
        func_0014DC98(p->pa, 2);
    }
    func_001A20F8(p, q);
}
