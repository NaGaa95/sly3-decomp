// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00160960 (from scratch): state change - leave the old state, then per-state setup (owns the three jump tables
// 0x3209F0/0x320A50/0x320A90; the -2275 gravity vector before them is D_003209E0). Keys: C++ so the VU_FLOAT temps share
// sp+0 with the by-value GRF copy; per-case statements left as written so jump2 cross-jumps the shared Enter() tails;
// case 8: MulF with 2 extra allocation-only "j"(f.q) operands (temp vf1) and 'SO *pso' + 'float r' read before the temps.
typedef int qword __attribute__((mode(TI)));
struct VE { short d, pad; void (*pfn)(); };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct GRF { unsigned char ab[16]; };
struct XF { char pad[0x30]; qword pos; };
struct HIT { qword pos; float x10, x14; int pad18[2]; int kind; };
struct SO { char pad[0x40]; struct { char pad[0x68]; float r; } *pdim; char pad44[0x60 - 0x44]; qword vAccel; char pad70[0x7C - 0x70]; float x7C, x80; };
struct EXPL { char pad[4]; SO *pso; };
struct OBJ { char pad[0xC]; VE *pvt; char pad10[0x30 - 0x10]; qword x30, x40; };
struct ST { char pad[0xC]; VE *pvt; char pad10[0x3C - 0x10]; int n; char pad40[0xCC - 0x40]; int xCC; char padD0[0xF4 - 0xD0]; float xF4; char padF8[0xFC - 0xF8]; float xFC; };
struct ACT { char pad[0xC]; VE *pvt; char pad10[0x130 - 0x10]; int x130; char pad134[0x29C - 0x134]; char x29C[0x2F4 - 0x29C]; GRF grf; char pad304[0x18B4 - 0x304]; OBJ *x18B4; };
struct S { char pad[0x10]; ACT *pact; char pad14[0x18 - 0x14]; char x18[0x30 - 0x18]; int state; float t; char pad38[0x50 - 0x38]; int x50; char pad54[0x60 - 0x54]; qword x60; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern float D_003457A8, D_003457AC;
extern const union QV { float af[4]; qword q; } D_003209E0; /* {0, 0, -2275, 0} */
extern char D_00475480[], D_0036C700[], D_00317490[];
void func_00256DF0(ACT *);
void func_00240DB0(ACT *);
void func_001A9420(void *, int, int);
void func_001A94F0(void *, int);
void func_001A93C8(void *, int, int);
void func_001A94A8(void *, int);
void func_00238AE8(void *);
ST *func_00238690(void *, int);
void func_001614E8(S *, int);
GRF func_00252AD0(int);
EXPL *func_00255130(ACT *, GRF);
void func_00132930(ST *, qword);
void func_002BC760(qword *, HIT *);
ACT *func_001F4A80(ACT *);
void func_0024E8E8(ACT *, qword);
void func_001854C8(void *, int, ACT *);
void func_00256FB0(ACT *, HIT *);
qword func_0015FB28(S *);
void func_001C7A00(OBJ *, int, int);
void func_001FE728(OBJ *, int);
void func_00160960(S *p, int state, HIT *phit);
}
static inline void Enter(ST *pst) { VE *e = &pst->pvt[8]; ((void (*)(ST *))e->pfn)((ST *)((char *)pst + e->d)); }
static inline XF *Xf(ACT *p) { VE *e = &p->pvt[36]; return ((XF *(*)(ACT *))e->pfn)((ACT *)((char *)p + e->d)); }
static inline void SetV(OBJ *p, qword v) { VE *e = &p->pvt[34]; ((void (*)(OBJ *, qword))e->pfn)((OBJ *)((char *)p + e->d), v); }
static inline void SetP(OBJ *p, void *v) { VE *e = &p->pvt[35]; ((void (*)(OBJ *, void *))e->pfn)((OBJ *)((char *)p + e->d), v); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulF(qword a, const VU_FLOAT &f) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(f.q), "j"(f.q), "j"(f.q)); return r; }
static inline qword DivF(qword a, const VU_FLOAT &f) { qword r; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(f.q)); return r; }
static inline GRF Or(const GRF &a, const GRF &b) { GRF r; for (int i = 0; i < 16; i++) r.ab[i] = a.ab[i] | b.ab[i]; return r; }

void func_00160960(S *p, int state, HIT *phit)
{
    int old = p->state;
    if (old == state && state != 13)
        return;
    switch (old) {
    case 15: func_00256DF0(p->pact); break;
    case 12: func_00240DB0(p->pact); break;
    case 18: p->x50 = 0; break;
    case 20:
        func_00240DB0(p->pact);
        func_001A9420(D_00475480, p->pact->x130, 2);
        func_001A94F0(D_00475480, p->pact->x130);
        break;
    }
    func_00238AE8(p->x18);
    p->state = state;
    p->t = g_clock.t;
    switch (state) {
    case 2: { ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 1; Enter(pst); break; }
    case 0: { ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 2; Enter(pst); break; }
    case 20: {
        func_001614E8(p, -1);
        ST *pst = func_00238690(p->pact->x29C, 0xC9);
        pst->n = 2;
        Enter(pst);
        func_001A93C8(D_00475480, p->pact->x130, 2);
        func_001A94A8(D_00475480, p->pact->x130);
        break;
    }
    case 1: { ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 13; Enter(pst); break; }
    case 3: { ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 14; Enter(pst); break; }
    case 4: { ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 15; Enter(pst); break; }
    case 5: case 6: case 7: case 8: case 19: {
        int n = -1;
        ST *pst = func_00238690(p->pact->x29C, 0xCB);
        switch (p->state) {
        case 5: case 6: n = 0x15; break;
        case 8: n = 0x18; break;
        case 7: n = 0x17; break;
        case 19: n = 0x1A; break;
        }
        EXPL *pexpl = func_00255130(p->pact, Or(p->pact->grf, func_00252AD0(n)));
        float x7C = pexpl->pso->x7C;
        float x80 = pexpl->pso->x80;
        switch (p->state) {
        case 5:
            pexpl->pso->x7C = D_003457A8;
            pexpl->pso->x80 = 450.0f;
            pexpl->pso->vAccel = DivF(D_003209E0.q, VU_FLOAT(pexpl->pso->pdim->r * pexpl->pso->pdim->r));
            pst->xCC = 3;
            break;
        case 8:
            pexpl->pso->x80 = 2000.0f;
            pexpl->pso->x7C = 1200.0f;
            { SO *pso = pexpl->pso; float r = pso->pdim->r; pso->vAccel = DivF(MulF(D_003209E0.q, VU_FLOAT(0.75f)), VU_FLOAT(r * r)); }
            pst->xCC = 3;
            break;
        case 7:
            pexpl->pso->x7C = D_003457AC;
            pexpl->pso->x80 = 450.0f;
            pexpl->pso->vAccel = DivF(D_003209E0.q, VU_FLOAT(pexpl->pso->pdim->r * pexpl->pso->pdim->r));
            pst->xCC = 8;
            break;
        case 19:
            pexpl->pso->x80 = 1200.0f;
            pexpl->pso->x7C = 900.0f;
            pexpl->pso->vAccel = DivF(D_003209E0.q, VU_FLOAT(pexpl->pso->pdim->r * pexpl->pso->pdim->r));
            pst->xCC = 3;
            break;
        case 6:
            pst->xCC = 9;
            break;
        }
        pst->n = n;
        Enter(pst);
        pexpl->pso->x7C = x7C;
        pexpl->pso->x80 = x80;
        break;
    }
    case 9: {
        ST *pst = func_00238690(p->pact->x29C, 0xCB);
        pst->xCC = 4;
        func_00132930(pst, phit->pos);
        pst->xFC = phit->x10;
        pst->xF4 = phit->x14;
        Enter(pst);
        break;
    }
    case 10: { ST *pst = func_00238690(p->pact->x29C, 0xCB); pst->n = 0x16; pst->xCC = 6; Enter(pst); break; }
    case 11: { func_001614E8(p, -1); ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 3; Enter(pst); break; }
    case 12: {
        func_001614E8(p, -1);
        ST *pst = func_00238690(p->pact->x29C, 0xE5);
        ((OBJ *)pst)->x30 = phit->pos;
        ((OBJ *)pst)->x40 = *(qword *)&phit->x10;
        Enter(pst);
        break;
    }
    case 13: {
        func_001614E8(p, -1);
        ST *pst = func_00238690(p->pact->x29C, 0xCE);
        func_002BC760(&((OBJ *)pst)->x30, phit);
        Enter(pst);
        break;
    }
    case 14: {
        func_001614E8(p, -1);
        ST *pst = func_00238690(p->pact->x29C, 0xC9);
        if (!phit || phit->kind == 0x2000 || phit->kind == 0x4000) {
            pst->n = 0x1E;
            qword pos = Xf(func_001F4A80(p->pact))->pos;
            func_0024E8E8(p->pact, Sub(pos, Xf(p->pact)->pos));
        } else {
            pst->n = 7;
        }
        Enter(pst);
        func_001854C8(D_0036C700, 0x10, p->pact);
        break;
    }
    case 15: { func_001614E8(p, -1); func_00256FB0(p->pact, phit); ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 0x1B; Enter(pst); break; }
    case 16: { func_001614E8(p, -1); ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 0x1D; Enter(pst); break; }
    case 17: {
        func_001614E8(p, -1);
        ST *pst = func_00238690(p->pact->x29C, 0xC9);
        pst->n = 0x1C;
        Enter(pst);
        p->x60 = func_0015FB28(p);
        OBJ *po = p->pact->x18B4;
        if (po) {
            func_001C7A00(po, 0, 0);
            SetV(po, p->x60);
            SetP(po, D_00317490);
            func_001FE728(po, 1);
        }
        break;
    }
    case 18: { func_001614E8(p, -1); ST *pst = func_00238690(p->pact->x29C, 0xC9); pst->n = 0x19; Enter(pst); break; }
    }
}
