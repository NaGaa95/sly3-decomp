// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of a hero's action context (Sly 3 version of Sly 2 func_001911A8): dispatches on the context's action and
// loops while an action changed the step (and not to -1). Action 8 / step "other" probes the ground below the actor:
// a box query along the up axis with a line test against every found object (any hit with a nonzero parameter aborts),
// then a sphere around the actor's world bounds is pruned against every object's BSP and turned into contacts; any
// contact aborts, otherwise step 8 is entered. GLengthNop adds the mtc1 hazard nop that the default assembler would insert
// (this file needs gnu-2.9 so that the 14-entry jump table is not padded).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
union U { qword q; float f[4]; int i[4]; };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *fn; };
struct PADOBJ { char pad0[8]; float amount; char pad0C[0xC]; uint grfbtn; char pad1C[0x2C - 0x1C]; VTE *vt; };
struct SURF;
struct BSP { BSP *pbspNeg, *pbspPos; SURF *psurf; };
struct XP;
struct SW;
struct ASEGA;
struct GEOM { int cpos; qword *apos; };
struct SODESC { char pad0[0xA4]; int stamp; };
struct BSPS { int x0; int cbsp; int x8; BSP *absp; };
struct SO {
    SODESC *pdesc; char pad4[0x18 - 4]; ulong flags; char pad20[0x78 - 0x20]; BSPS bsps; char pad88[0xA0 - 0x88]; GEOM geomWorld;
    char padA8[0xC0 - 0xA8]; int stamp;
};
struct LSG { qword apos[2]; qword anormal[2]; float au[2]; int lsgk; void *apsurf[2]; void *pedge; int iiposSwap; LSG *plsgNext; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0xDC - 0x10]; void *pvFilter; char padE0[0x134 - 0xE0]; PADOBJ *pjoy;
    char pad138[0x260 - 0x138]; qword posOffset; char pad270[0x298 - 0x270]; SO *pso; char pad29C[0x101C - 0x29C];
    ACTOR *ptarget; float gTarget; char pad1024[0x113C - 0x1024]; ASEGA *pasega;
};
struct ATTACH { char pad0[0x34]; ACTOR *pactor; };
struct CONTEXT {
    ACTOR *pactor; float tStamp; int action; int step; float tHold; ACTOR *pactorFocus; char pad18[8]; float gParam;
    char pad24[0x440 - 0x24]; ATTACH attach; char pad478[0x500 - 0x478]; int fInhibit;
};
struct CLOCK { float time, dt; };
struct ALLOCREQ { int cb; int cbAlign; };
struct FRAME { FRAME(); ~FRAME(); };
struct VU_FLOAT { qword q; };

extern "C" {
extern SW D_00475480;
extern CLOCK D_0036BB98;
extern PADOBJ D_0036E6D0;
extern qword D_00317550;
int func_00156998(ACTOR *);
int func_001A7A80(PADOBJ *, uint, float);
void func_001B7268(void *, int, int, ACTOR *, float);
void func_001BDA88(void *, int, int);
int func_00138AC8(ASEGA *);
void func_001B4430(CONTEXT *, int);
void func_001561F0(ACTOR *, ACTOR *);
int func_0013B500(ACTOR *, int);
int func_00154DA0(ACTOR *);
void func_002091B0(ATTACH *, ACTOR *);
int func_0025CDD0(void *, SO *);
void func_0025CF18(SW *, qword, qword, int (*)(void *, SO *), void *, int *, SO ***);
int func_00164A10(SO *, qword, qword, int, LSG *);
void func_0018B1E0(SO *);
qword func_00120E80(int, qword *);
qword func_00120EB0(int, qword *);
void func_001CD858(SW *, SO *, SO *, int, BSP *, XP **);
int func_00119C20(BSP *, BSP *, float, qword, int *, BSP **);
void func_001CC790(SW *, SO *, SO *, int, BSP *, BSP *, XP **);
void func_001CBAA0(SW *, XP *);
}
void *PvAllocSlot(ALLOCREQ *);

static inline void SetControl(ACTOR *p, int n) { VTE &v = p->vt[99]; ((void (*)(void *, int))v.fn)((char *)p + v.d, n); }
static inline int Can(ACTOR *p, int n) { VTE &v = p->vt[113]; return ((int (*)(void *, int))v.fn)((char *)p + v.d, n); }
static inline void Notify(ACTOR *p, ACTOR *q) { VTE &v = p->vt[55]; ((void (*)(void *, ACTOR *))v.fn)((char *)p + v.d, q); }
static inline qword Position(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.d)->r[3].q; }
static inline int PadHeld(PADOBJ *pad) { VTE &e = pad->vt[1]; return ((int (*)(void *, unsigned, float))e.fn)((char *)pad + e.d, 0x400, 0.15f); }
static inline void PadClear(PADOBJ *pad) { VTE &e = pad->vt[2]; ((void (*)(void *, unsigned))e.fn)((char *)pad + e.d, 0x400); }
static inline void *PvAllocStack(int cb) { ALLOCREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSlot(&req); }

static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwScale(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g.q)); return r; }
static inline qword QwCombine(qword a, qword b, VU_FLOAT g0, VU_FLOAT g1)
{
    qword r;
    __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(g0.q), "j"(b), "j"(g1.q));
    return r;
}
static inline float GFromVf(qword v) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v)); return g; }
static inline float GLength(const qword &v)
{
    qword qw, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(qw), "=j"(one) : "j"(v));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(qw) : "0"(qw));
    return GFromVf(qw);
}
static inline float GLengthNop(const qword &v)
{
    qword qw, one;
    float f;
    __asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(qw), "=j"(one) : "j"(v));
    __asm__("vsqrt Q,%0x
	vwaitq
	vaddq.x %0,$vf0,Q" : "=j"(qw) : "0"(qw));
    __asm__("mtc1 %1,%0
	nop" : "=f"(f) : "r"(qw));
    return f;
}
static inline int Min(int a, int b) { return a < b ? a : b; }

static inline void ProbeGround(CONTEXT *p)
{
    FRAME scope;
    LSG alsg[8];
    int i;
    qword pos = Position(p->pactor);
    qword posBase = QwAdd(pos, p->pactor->posOffset);
    qword posEnd = QwAdd(posBase, QwScale(D_00317550, VuFloat(200.0f)));
    int cso;
    SO **apso;
    register int *pcso __asm__("$21");   // pin: &cso in s5 (pad then lands in s4)
    pcso = &cso;
    func_0025CF18(&D_00475480, posEnd, posBase, func_0025CDD0, p->pactor->pvFilter, pcso, &apso);
    for (i = 0; i < cso; i++) {
        LSG *plsg = alsg;
        int clsg = func_00164A10(apso[i], posBase, posEnd, 8, plsg);
        for (int j = 0; j < clsg; j++)
            if (plsg[j].au[0] != 0.0f)
                return;
    }
    SO *psoSelf = p->pactor->pso;
    if (psoSelf->stamp != psoSelf->pdesc->stamp)
        func_0018B1E0(psoSelf);
    GEOM *pgeom = &psoSelf->geomWorld;
    int cbspMax = 0;
    qword posMin = func_00120E80(pgeom->cpos, pgeom->apos);
    qword posMax = func_00120EB0(pgeom->cpos, pgeom->apos);
    func_0025CF18(&D_00475480, posMin, posMax, func_0025CDD0, p->pactor->pvFilter, pcso, &apso);
    for (i = 0; i < cso; i++)
        if (cbspMax <= apso[i]->bsps.cbsp)
            cbspMax = apso[i]->bsps.cbsp;
    cbspMax = Min(cbspMax, 0x1555);
    BSP *absp = (BSP *)PvAllocStack(cbspMax * sizeof(BSP));
    qword posMid = QwCombine(posMin, posMax, VuFloat(0.5f), VuFloat(0.5f));
    float sRadius = GLength(QwSub(posMid, posMin));
    for (i = 0; i < cso; i++) {
        SO *pso = apso[i];
        XP *pxp = 0;
        if (pso->flags & (1UL << 17)) {
            func_001CD858(&D_00475480, pso, psoSelf, 0, 0, &pxp);
        } else {
            int cbspLeft = cbspMax;
            BSP *pbsp = absp;
            if (pso->stamp != pso->pdesc->stamp)
                func_0018B1E0(pso);
            BSPS *pbs = &pso->bsps;
            if (func_00119C20(pbs->absp, (BSP *)0x7FFFFFFF, sRadius, posMid, &cbspLeft, &pbsp) == 2) {
                int cbsp = pbsp - absp;
                pbsp--;
                func_001CC790(&D_00475480, psoSelf, pso, cbsp, pbs->absp, pbsp, &pxp);
            }
        }
        if (pxp) {
            func_001CBAA0(&D_00475480, pxp);
            return;
        }
    }
    func_001B4430(p, 8);
}

extern "C" void func_001B27D8(CONTEXT *p)
{
    PADOBJ *pad = func_00156998(p->pactor) ? &D_0036E6D0 : p->pactor->pjoy;
    int step;
    do {
        step = p->step;
        switch (p->action) {
        case 1:
            if (0.15f < D_0036BB98.time - p->tHold && func_001A7A80(pad, 0x40, 0.25f)) {
                func_001B7268((char *)p->pactor + 0x320, 7, 0, p->pactorFocus, 1.0f);
                break;
            }
            if (PadHeld(pad) && Can(p->pactor, 3)) {
                PadClear(pad);
                func_001BDA88((char *)p->pactor + 0xF60, 0, 0);
            }
            break;
        case 3:
        case 4:
            if (func_001A7A80(pad, 0x40, 0.1f)) {
                float g = p->action == 4 ? *(float *)((char *)p->pactorFocus + 0x11C) : *(float *)((char *)p->pactorFocus + 0x1DC);
                func_001B7268((char *)p->pactor + 0x320, 1, 0, 0, g);
                break;
            }
            if (PadHeld(pad) && Can(p->pactor, 3)) {
                PadClear(pad);
                func_001BDA88((char *)p->pactor + 0xF60, 0, 0);
            }
            break;
        case 7: {
            ACTOR *pactorFocus = p->pactorFocus;
            SetControl(p->pactor, 0);
            Notify(pactorFocus, p->pactor);
            break;
        }
        case 14: {
            ACTOR *pactorFocus = p->pactorFocus;
            SetControl(p->pactor, 0);
            func_001561F0(p->pactor, pactorFocus);
            break;
        }
        case 8:
            switch (step) {
            case 7:
                if (func_00138AC8(p->pactor->pasega))
                    func_001B4430(p, 9);
                break;
            case 8:
                if (func_00138AC8(p->pactor->pasega))
                    SetControl(p->pactor, 0);
                break;
            default:
                ProbeGround(p);
                break;
            }
            break;
        case 9:
            if (GLengthNop(QwSub(Position(p->pactorFocus), Position(p->attach.pactor))) < 25.0f) {
                func_002091B0(&p->attach, p->pactorFocus);
                SetControl(p->pactor, 0);
            }
            break;
        case 10:
            if (!p->pactor->pasega || func_00138AC8(p->pactor->pasega)) {
                SetControl(p->pactor, 0);
            } else if (0.35f < D_0036BB98.time - p->tStamp) {
                if (0.0f < p->pactor->pjoy->amount || (p->pactor->pjoy->grfbtn & 0xD0)) {
                    SetControl(p->pactor, 0);
                    return;
                }
            }
            break;
        case 11:
        case 12:
            if (!p->pactor->pasega || func_00138AC8(p->pactor->pasega))
                SetControl(p->pactor, 0);
            break;
        case 5:
            if (func_0013B500(p->pactorFocus, 10) && func_00154DA0(p->pactor)) {
                p->pactor->ptarget = p->pactorFocus;
                p->pactor->gTarget = p->gParam;
                SetControl(p->pactor, 8);
            }
            break;
        case 2:
            break;
        default:
            if (func_001A7A80(pad, 0x40, 0.1f)) {
                func_001B7268((char *)p->pactor + 0x320, 1, 0, 0, 1.0f);
                break;
            }
            if (PadHeld(pad) && Can(p->pactor, 3) && (p->action == 0 || p->action == 13)) {
                PadClear(pad);
                func_001BDA88((char *)p->pactor + 0xF60, 0, 0);
                break;
            }
            if (p->fInhibit)
                break;
            if (pad->grfbtn & 0x20)
                break;
            SetControl(p->pactor, 0);
            break;
        }
    } while (p->step != step && p->step != -1);
}
