// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00138270: adapted from the matched Sly 2 source src/hand/func_00131290.cpp (Sly 3 event kinds, calls and offsets).
struct EV { float g0; unsigned int k; void *pv; union { float g; int n; } uC; int x10; };
struct Q { char pad[0x90]; int cev; struct EV *aev; };
struct A0 { int x0; int x4; int x8; int xC; float g10; float g14; float g18; };
struct A20 { int x0; int x4; float g8; };
struct MSG;
struct B { int pad[3]; virtual void Begin(); virtual void End(); virtual void F3(int, int, int, void **, int); virtual void F4(int, struct MSG *); };
struct P : B { int x10; struct Q *pq; void *po; float g1C; char pad2[0x40 - 0x20]; float g40;
    char pad3[0x5C - 0x44]; char a5C[4]; };
struct G { P *p; G(P *pp) : p(pp) { p->Begin(); } ~G() { p->End(); } };
struct MSG { struct P *p; float g; void *pv; };
struct O3 { char pad[0x130]; int n130; };
struct S11C0 { char b[0x11C0]; };
struct GL { char pad[0x3EB8]; int c; void *a[1]; };
extern "C" {
extern struct GL D_00475480;
extern struct S11C0 D_0036E740[];
void *func_00138258(struct P *);
void func_0025DB38(void *, int, int, int, int, void *, void *, struct Q *, void *, float, float, float);
void func_0025DCA8(void *, void *, struct Q *, void *);
void *func_0017E1B8(void *, int, int, void *);
void *func_001F4A80(void *);
void func_00167D38(void *, void *);
void func_001A9058(void *, void *, float);
int func_0013B500(void *, int);
void func_00136908(void *, int, int, int, float, float);
void func_00225EE8(void *, int);
void func_0017D7D0(void *);
void func_0014CE20(void *);
void func_00137D08(struct P *, int, int, float, float);
void func_00137B00(struct P *);
void func_00138AF0(struct P *, int);
void func_0025D740(void *, int, void *, void *, struct Q *, float);
void func_0025D940(void *, int, int, void *, struct Q *, float);
void func_0025D810(void *, int, void *, int, void *, void *, struct Q *);
void func_0025D8A8(void *, int, void *, int, void *, void *, struct Q *);
void func_00185420(void *, float);
void func_00185480(void *);
void func_0025DA70(void *, int, int, void *, struct Q *, float);
void func_0028F978(struct P *, void *);
void func_00241A38(void *, int);
void func_00155AB8(void *, void *, void *, void *);
void func_001399F0(void *);
void func_001399A0(void *);
}
extern "C" void func_00138270(struct P *p, struct EV *pev)
{
    G g(p);
    struct MSG msg;
    void *pv;
    struct Q *pq;
    int f;
    p->g1C = pev->g0;
    pq = p->pq;
    f = 0;
    if (p->g40 < 0.0f && pev >= pq->aev)
        f = pev < pq->aev + pq->cev;
    switch (pev->k) {
    case 0: {
        void *v = func_00138258(p);
        struct A0 *pa = (struct A0 *)pev->pv;
        func_0025DB38(&D_00475480, pa->x0, pa->x4, pa->x8, pa->xC, p->po, v, pq, p->a5C, pa->g10, pa->g14, pa->g18);
        break;
    }
    case 1:
        func_0025DCA8(&D_00475480, pev->pv, pq, p->a5C);
        break;
    case 2: {
        void *o = 0;
        if (pev->uC.n != -1) {
            void *po = func_0017E1B8(&D_00475480, 4, pev->uC.n, func_00138258(p));
            if (po)
                o = func_001F4A80(po);
        }
        if (o) {
            func_00167D38(o, pev->pv);
        } else {
            int i;
            for (i = 0; i < D_00475480.c; i++)
                func_00167D38(D_00475480.a[i], pev->pv);
        }
        break;
    }
    case 3: {
        struct S11C0 *o = 0;
        if (pev->x10 == -1) {
            o = D_0036E740;
        } else {
            struct O3 *po = (struct O3 *)func_0017E1B8(&D_00475480, 4, pev->x10, func_00138258(p));
            if (po && po->n130 != -1)
                o = &D_0036E740[po->n130];
        }
        if (o)
            func_001A9058(o, pev->pv, pev->uC.g);
        break;
    }
    case 4: {
        void *po = func_0017E1B8(&D_00475480, 4, (int)pev->pv, func_00138258(p));
        if (po) {
            if (func_0013B500(po, 0x82))
                func_00136908(po, 0, 0, 0, 0.0f, 1.0f);
            else if (func_0013B500(po, 0x87))
                func_00225EE8(po, 0);
            else if (func_0013B500(po, 0x8A))
                func_0017D7D0(po);
            else if (func_0013B500(po, 0x59))
                func_0014CE20(po);
        }
        break;
    }
    case 5:
        func_00137D08(p, 0, 0, *(float *)&pev->pv, pev->uC.g);
        break;
    case 6:
        func_00137B00(p);
        break;
    case 9:
    case 10:
        {
            int fT = (pev->k == 9);
            fT ^= f;
            func_00138AF0(p, fT);
        }
        break;
    case 7:
    case 8: {
        int fT = (pev->k == 7);
        fT ^= f;
        func_0025D740(&D_00475480, fT, pev->pv, func_00138258(p), pq, pev->uC.g);
        break;
    }
    case 11: {
        msg.p = p;
        msg.g = pev->g0;
        msg.pv = pev->pv;
        p->F4(10, &msg);
        break;
    }
    case 12: {
        { void **ppv = &pv; *ppv = &pev->pv; p->F3(4, 0, 1, ppv, 0); }
        break;
    }
    case 17: {
        struct A20 *pa = (struct A20 *)pev->pv;
        func_0025D940(&D_00475480, pa->x0, pa->x4, func_00138258(p), pq, pa->g8);
        break;
    }
    case 13:
    case 14: {
        int fT = (pev->k == 13);
        fT ^= f;
        func_0025D810(&D_00475480, fT, pev->pv, pev->uC.n, p->po, func_00138258(p), pq);
        break;
    }
    case 15:
    case 16: {
        int fT = (pev->k == 15);
        fT ^= f;
        func_0025D8A8(&D_00475480, fT, pev->pv, pev->uC.n, p->po, func_00138258(p), pq);
        break;
    }
    case 18:
        func_00185420(&D_00475480, p->g1C);
        break;
    case 19:
        func_00185480(&D_00475480);
        break;
    case 20: {
        struct A20 *pa = (struct A20 *)pev->pv;
        func_0025DA70(&D_00475480, pa->x0, pa->x4, func_00138258(p), pq, pa->g8);
        break;
    }
    case 21:
        func_0028F978(p, pev->pv);
        break;
    case 22:
        func_00241A38(p->po, (int)pev->pv);
        break;
    case 23:
        func_00241A38(p->po, -1);
        break;
    case 24:
        if (p->po && func_0013B500(p->po, 0x33)) {
            char *pb = (char *)pev->pv;
            func_00155AB8(p->po, pb, pb + 8, pb + 0x10);
        }
        break;
    case 25:
    case 26:
        if (p->po) {
            void *o = func_0017E1B8(&D_00475480, 1, (int)pev->pv, p->po);
            if (o) {
                if (pev->k == 25)
                    func_001399F0(o);
                else
                    func_001399A0(o);
            }
        }
        break;
    }
}
