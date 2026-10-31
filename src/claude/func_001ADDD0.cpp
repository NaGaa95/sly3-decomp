// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001ADDD0: Sly 3 SetJtJts (port of Sly 2 func_0018C250).
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct VECTOR { float x, y, z; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct OBJ { char pad0[0xC]; VTE *vt; };
struct SOX { char pad0[0xC]; VTE *vt; char pad10[0x40]; void *x50; };
struct ASEG { char pad0[0x64]; float tMax; float svtMaster; };
struct ASEGA { char pad0[0xC]; VTE *vt; char pad10[0x4]; ASEG *paseg; char pad18[0x4]; float tLocal; };
struct SM;
struct GAIT { int x0; ASEG *pasegbl; };
struct HND { char pad0[0xC]; VTE *vt; char pad10[0xDC]; void *ptn; char padF0[0x58]; int nKind; char pad14C[0x4]; int sfxidHangStart; int sfxid; };
struct XA { int x0; void *pso; };
struct ACT { char pad0[0x20]; VECTOR v; };
struct X140 { char pad0[0x20]; VECTOR v; };
struct X144C { char pad0[0xC]; VTE *vt; char pad10[0x130]; X140 *x140; };
struct XFP { char pad0[0xA0]; void *xA0; };
struct X1F20 { char pad0[0x4C]; float x4C; char pad50[0x22C]; int x27C; };
struct X18EC { char pad0[0x18EC]; OBJ *x18EC; };
struct LM { float low, high; };
struct POLY { float a, b, c; };
struct CLOCK { float t; };
struct SND;
struct VU_FLOAT { qword qw; };
struct JT {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x34];
    XFP *x44;
    XFP *x48;
    XFP *x4C;
    void *x50;
    char pad54[0x114];
    OBJ *x168;
    char pad16C[0x34];
    VECTOR4 v1A0;
    float uGait;
    char pad1B4[0x8];
    float radTarget;
    MATRIX3 matTarget;
    char pad1F0[0x20];
    float x210;
    char pad214[0x10C];
    char jtair[1];
    char pad324[0x34];
    float zStart;
    char pad35C[0x30];
    void *ploAir;
    char pad390[0x170];
    char jtgrab[1];
    char pad504[0x4];
    int nState;
    char pad50C[0x518];
    int xA24;
    char padA28[0x418];
    char xE40[1];
    char padE41[0x11F];
    char xF60[1];
    char padF61[0xAF];
    char x1010[1];
    char pad1011[0xB];
    void *x101C;
    char pad1020[0xE8];
    void *x1108;
    float radLeft;
    char pad1110[0x10];
    qword x1120;
    char pad1130[0x4];
    SM *x1134;
    SM *x1138;
    ASEGA *x113C;
    OBJ *x1140;
    int x1144;
    char pad1148[0x1C];
    int x1164;
    char pad1168[0x4C];
    OBJ *x11B4;
    int x11B8;
    char pad11BC[0xD4];
    char x1290[1];
    char pad1291[0x1BB];
    X144C *x144C;
    char pad1450[0x4];
    char *x1454;
    char pad1458[0x18];
    GAIT gait1470;
    char pad1478[0x1A8];
    ASEG *x1620;
    char pad1624[0x28];
    int x164C;
    char pad1650[0x2A0];
    char x18F0[1];
    char pad18F1[0xEF];
    int jts;
    float tJts;
    int jtbs;
    float tJtbs;
    int x19F0;
    HND *phnd;
    float tHang;
    int x19FC;
    int x1A00;
    XA *x1A04;
    char pad1A08[0x48];
    SM *x1A50;
    char pad1A54[0xC];
    qword x1A60;
    char pad1A70[0x24];
    ASEG *x1A94;
    float x1A98;
    float x1A9C;
    char pad1AA0[0x4];
    SOX *x1AA4;
    char pad1AA8[0x10];
    ASEG *x1AB8;
    ASEG *x1ABC;
    char pad1AC0[0x8];
    void *x1AC8;
    char pad1ACC[0x3C];
    ACT *x1B08;
    char pad1B0C[0x4];
    void *x1B10;
    void *x1B14;
    char pad1B18[0x108];
    ASEG *x1C20;
    SM *x1C24;
    ASEG *x1C28;
    int x1C2C;
    char pad1C30[0x60];
    GAIT gait1C90;
    char pad1C98[0xB4];
    int x1D4C;
    char pad1D50[0x100];
    ASEG *x1E50;
    char pad1E54[0x1C];
    ASEG *x1E70;
    ASEG *x1E74;
    ASEG *x1E78;
    char pad1E7C[0x14];
    char x1E90[1];
    char pad1E91[0x33];
    float x1EC4;
    char pad1EC8[0x8];
    float x1ED0;
    char pad1ED4[0x8];
    float x1EDC;
    char pad1EE0[0x8];
    ASEG *x1EE8;
    int x1EEC;
    int x1EF0;
    char pad1EF4[0xC];
    int x1F00;
    int x1F04;
    void *x1F08;
    char pad1F0C[0x14];
    X1F20 *x1F20;
    char pad1F24[0x14];
    SM *x1F38;
    ASEG *x1F3C;
};
extern "C" {
extern CLOCK g_clock;
extern qword D_00317560;
extern char D_00475480[];
extern X18EC *D_0038AE90;
extern POLY D_00322730;
extern LM D_00322740;
SND *func_002459F8(int sfxid);
void func_00244F08(SND *psnd, void *pv);
void func_00208B20(void *p, int n);
void func_001FE728(void *pexpl, int n);
void func_001B77F8(void *pjtair, int n, int m);
void func_0013BD88(void *pv, void *pvRef);
void func_0028EDC8(void *pso, void *pxf, void *pact);
void func_002811F0(void *pso, void *pxa);
void func_00281178(void *psw, void *pxa);
void func_001BFAD0(void *p, int n);
void func_001B4430(void *p, int n);
void func_001C21F0(void *p, int n);
void func_002734E8(void *p, int n);
void func_00140CD0(void *p, int n);
int func_00140BF0(void *p);
void func_0028F068(void *pso, void *pxf, int nRole);
void func_00155328(void *p);
void func_00155310(void *p, int n);
int func_00138AC8(ASEGA *p);
int func_0013B500(void *p, int cid);
void func_00255960(void *p);
void func_0024F3B8(void *pjt, void *phnd, int f);
void func_001F47C8(void *pjt, void *ptn);
void func_0024F1E8(void *pjt, float g);
void func_001C7A00(void *pjt, int a, int b);
void func_001309D8(void *p);
void *func_002387A8(void *p, int n);
void func_0018BB20(void *p, int n);
void func_00169C40(void *p);
void func_00279140(void *p);
void func_0023B620(void *p, int f);
int func_00173428(void *p);
int func_00172CE0(void *p);
SM *func_001733F8(void *p);
GAIT *func_00173408(void *p);
int func_00239A78(SM *psm, int oid);
void func_00258F28(GAIT *pgait);
void func_0028ECE0(void *pso, void *pxf, void *pact);
qword func_001B2070(void *pjt);
void func_001B2430(void *pjt);
void func_0013BD00(void *pv, void *pvRef);
float func_001B2038(void *pjt);
float func_0011E3B8(float rad);
void func_0024E878(void *pjt, float rad);
void func_001B0FF0(void *pjt);
void func_001BDBB0(void *p, int n);
void func_001AFF00(void *pjt);
void func_0024F0B0(void *pjt);
void func_0024E8E8(void *pjt, qword v);
float func_001368E0(ASEG *paseg, int oid);
void func_00137070(float t, float svt, ASEG *paseg, void *palo, void *pxfPart, void *pxfRoot, MATRIX4 *pmat, int n);
qword func_001AFE60(void *pjt);
void func_00148938(ASEG *p);
MATRIX4 func_0028EC08(void *a, void *b, MATRIX4 *pmat);
int func_00130078(void *pjt, void *pxf, int a, int b, int c, qword q);
qword func_0011D3C0(MATRIX4 *pmat);
void func_0024E920(void *pjt, void *p);
int func_001F4A80(void *pjt);
void *func_00169BF8(int cb);
void *func_0016C608(void *p, int a, int b, void *pjt, void *q);
void func_00169CE0(void *p);
void func_00279120(void *p, void *pjt);
void func_001B0450(void *pjt);
void func_001ADCA0(void *pjt, int grf);
void func_00137628(ASEGA **pp);
void func_0023AC58(OBJ **pp);
void func_00136908(ASEG *paseg, void *palo, float tStart, float svt, int grfapl, ASEGA **pp);
OBJ *func_002399F0(SM *psm, void *palo, int oid, int grfapl, int grfRoute);
}
static inline void ClearXyz(VECTOR *pvec)
{
    pvec->z = 0.0f;
    pvec->y = 0.0f;
    pvec->x = 0.0f;
}
static inline void SetXyz(VECTOR *pvec, float g)
{
    pvec->z = g;
    pvec->y = g;
    pvec->x = g;
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline VU_FLOAT VuFloatBits(float g)
{
    VU_FLOAT v;
    __asm__("mfc1 %0, %1" : "=r"(v.qw) : "f"(g));
    return v;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(qw));
    return z;
}
static inline qword QwScale(qword qwVec, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwVec), "j"(gScale.qw));
    return qw;
}
static inline qword QwDivide(qword qwVec, VU_FLOAT g)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(qwVec), "j"(g.qw));
    return qw;
}
static inline qword QwAddVelocity(VU_FLOAT t, qword pos, qword vel)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(qw) : "j"(pos), "j"(t.qw), "j"(vel));
    return qw;
}
static inline qword QwRotateVecRows(qword qwRow0, qword qwRow1, qword qwRow2, qword qwVec)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(qwResult)
            : "j"(qwRow0), "j"(qwRow1), "j"(qwRow2), "j"(qwVec));
    return qwResult;
}
static inline qword QwRotateVecV(qword qwVec, MATRIX3 *pmat)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(qwResult)
            : "j"(qwVec), "j"(*(qword *)pmat->mat[0]), "j"(*(qword *)pmat->mat[1]), "j"(*(qword *)pmat->mat[2]));
    return qwResult;
}
static inline float Evaluate(POLY *p, float t) { return p->a + t * (p->b + t * p->c); }
static inline float Limit(float f, LM *p) { float low = p->low, high = p->high, r; if (f < low) r = low; else if (high < f) r = high; else r = f; return r; }
#define VTHIS(p, e) ((char *)(p) + (e)->delta)
static inline MATRIX4 *PmatWorld(void *pv) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[36]; return ((MATRIX4 * (*)(void *)) e->fn)(VTHIS(p, e)); }
static inline qword PosWorld(void *pv) { return *(qword *)PmatWorld(pv)->mat[3]; }
static inline void HandleSplice(void *pv, int symid) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[3]; ((void (*)(void *, int, int, int, void *, int))e->fn)(VTHIS(p, e), symid, 0, 0, 0, 0); }
static inline void VCall(void *pv, int i) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[i]; ((void (*)(void *))e->fn)(VTHIS(p, e)); }
static inline void SetVelocity(void *pv, qword v) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[40]; ((void (*)(void *, qword))e->fn)(VTHIS(p, e), v); }
static inline void SetAngularVelocity(void *pv, qword v) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[41]; ((void (*)(void *, qword))e->fn)(VTHIS(p, e), v); }
static inline qword GetVelocity(void *pv) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[38]; return ((qword (*)(void *))e->fn)(VTHIS(p, e)); }
static inline int FCanUseGadget(void *pv, int n) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[113]; return ((int (*)(void *, int))e->fn)(VTHIS(p, e), n); }
static inline int GrfLeanMask(void *pv) { OBJ *p = (OBJ *)pv; VTE *e = &p->vt[111]; return ((int (*)(void *))e->fn)(VTHIS(p, e)); }
static inline int F1108(JT *p) { int f = 0; if (p->x1108) f = func_00173428(p->x1108) != 0; return f; }

extern "C" void func_001ADDD0(JT *pjt, int jts, int jtbs)
{
    ASEG *paseg = 0;
    int grf = 0;
    int oid = -1;
    int grfapl = 1;
    float tStart = 0.0f;
    float svt = 1.0f;
    SM *psm = 0;
    int grfRoute = 0x7FFC;
    int fKeep = 0;
    if (pjt->jts == jts && pjt->jtbs == jtbs)
        return;
    if (pjt->jts != jts)
    {
        if (jts == 3)
        {
            switch (pjt->jts)
            {
            case 4:
            case 0x11:
                pjt->ploAir = pjt->phnd;
                break;
            case 9:
                pjt->ploAir = pjt->x101C;
                break;
            default:
                pjt->ploAir = 0;
                break;
            }
        }
        switch (pjt->jts)
        {
        case 3:
            switch (jts)
            {
            case 4:
            case 9:
            case 0xE:
                break;
            case 8:
                if (pjt->nState == 1)
                    break;
            default:
            {
                SND *psnd = func_002459F8(0x3D);
                func_00244F08(psnd, pjt);
            }
            break;
            }
            func_00208B20(pjt->x18F0, -1);
            if (pjt->x1164 == 0)
            {
                void *pexpl = 0;
                switch (jts)
                {
                case 8:
                    switch (pjt->nState)
                    {
                    case 1:
                        break;
                    case 3:
                    case 4:
                        pexpl = pjt->x1B14;
                        break;
                    default:
                        pexpl = pjt->x1B10;
                        break;
                    }
                    break;
                case 0:
                case 2:
                case 6:
                case 0x13:
                    pexpl = pjt->x1B10;
                    break;
                }
                if (pexpl != 0)
                    func_001FE728(pexpl, 1);
            }
            func_001B77F8(pjt->jtair, -1, 0);
            break;
        case 4:
        {
            SND *psnd = func_002459F8(pjt->phnd->sfxid);
            func_00244F08(psnd, pjt);
            HandleSplice(pjt->phnd, 6);
            func_0013BD88(pjt->phnd, pjt);
            func_0028EDC8(pjt, pjt->x1AC8, pjt->x1B08);
            if (pjt->x1A04 != 0)
            {
                func_002811F0(pjt->x1A04->pso, pjt->x1A04);
                func_00281178(D_00475480, pjt->x1A04);
                pjt->x1A04 = 0;
            }
            func_001F47C8(pjt, 0);
            pjt->phnd = 0;
        }
        break;
        case 9:
            func_001BFAD0(pjt->x1010, -1);
            break;
        case 8:
            func_001B4430(pjt->jtgrab, -1);
            break;
        case 5:
            func_001C21F0(pjt->xE40, -1);
            break;
        case 0x12:
            func_002734E8(pjt->x1290, -1);
            break;
        case 7:
            func_00140CD0(pjt->x1E90, -1);
            break;
        case 0:
            func_0028F068(pjt, pjt->x48, 2);
            func_0028F068(pjt, pjt->x4C, 2);
            func_00155328(pjt);
            break;
        case 0xB:
            pjt->x11B8 &= ~2;
            break;
        case 1:
        case 2:
        case 0xA:
            pjt->uGait = pjt->x113C->tLocal / pjt->x113C->paseg->tMax;
            break;
        case 0xD:
            if (pjt->x113C != 0 && !func_00138AC8(pjt->x113C) && func_0013B500(pjt->x11B4, 0x3A))
                func_00255960(pjt->x11B4);
            pjt->x1D4C = 0;
            pjt->x11B8 &= ~4;
            break;
        case 0x11:
        {
            SND *psnd = func_002459F8(pjt->phnd->sfxid);
            func_00244F08(psnd, pjt);
            HandleSplice(pjt->phnd, 6);
            func_0013BD88(pjt->phnd, pjt);
            func_0024F3B8(pjt, pjt->phnd, 0);
            func_001F47C8(pjt, 0);
            pjt->phnd = 0;
        }
        break;
        case 0x13:
            pjt->x210 = 1.0f;
            pjt->radLeft = pjt->radTarget;
            func_0024F1E8(pjt, 1.0f);
            break;
        case 0x14:
        {
            int n = pjt->xA24;
            func_001C7A00(pjt, 0, 0xF);
            pjt->xA24 = n;
            func_001309D8(&pjt->x1F00);
            func_001309D8(&pjt->x1F04);
            func_0028F068(pjt, pjt->x48, 2);
            func_0028F068(pjt, pjt->x4C, 2);
        }
        break;
        case 0xE:
        case 0xF:
            func_0028F068(pjt, pjt->x48, 2);
            func_0028F068(pjt, pjt->x4C, 2);
            break;
        case 0x15:
        case 0x16:
            if (pjt->x1454 != 0 && jts != 0x16)
            {
                void *p = func_002387A8(pjt->x1454 + 0x29C, 0xE7);
                if (p != 0)
                    func_0018BB20(p, 0xB);
            }
            if (pjt->jts == 0x16)
            {
                VCall(pjt->x168, 56);
                func_00169C40(&pjt->x1F08);
            }
            break;
        case 0x18:
            func_00279140(pjt->x1F20);
            if (pjt->x144C != 0)
            {
                X140 *p = pjt->x144C->x140;
                if (p != 0)
                    SetXyz(&p->v, 1.0f);
                VCall(pjt->x144C, 9);
                func_0023B620(pjt->x144C, 0);
            }
            break;
        }
        switch (jts)
        {
        case -1:
            break;
        case 0:
        {
            if (F1108(pjt) || func_00172CE0(pjt->x1108) == 0x75D)
                psm = func_001733F8(pjt->x1108);
            if (psm == 0)
                psm = pjt->x1134;
            func_0028F068(pjt, pjt->x48, 1);
            func_0028F068(pjt, pjt->x4C, 1);
            pjt->x164C = 0;
            if (psm == pjt->x1134)
            {
                switch (pjt->jts)
                {
                case 1:
                    oid = 0x193;
                    break;
                case 0xA:
                    oid = 0x194;
                    break;
                case 0x17:
                    oid = 0x197;
                    break;
                case 3:
                {
                    int fHigh = pjt->x19F0;
                    if (fHigh == -1)
                    {
                        float dz = pjt->zStart - GZOfQw(PosWorld(pjt));
                        fHigh = 0;
                        if (400.0f < dz)
                            fHigh = 1;
                    }
                    oid = (fHigh == 1) ? 0x196 : 0x195;
                }
                break;
                default:
                    oid = 0x192;
                    break;
                }
                if (func_00239A78(psm, oid) < 0)
                    oid = -1;
                grfRoute = GrfLeanMask(pjt);
            }
            ClearXyz((VECTOR *)&pjt->v1A0);
            grf = 0x1F;
            func_00155310(pjt, 1);
        }
        break;
        case 2:
            paseg = pjt->gait1470.pasegbl;
            grfapl = 9;
            tStart = pjt->uGait * paseg->tMax;
            func_00258F28(&pjt->gait1470);
            break;
        case 7:
            func_00140CD0(pjt->x1E90, func_00140BF0(pjt->x1E90));
            fKeep = 1;
            break;
        case 4:
        {
            pjt->x19FC = -1;
            pjt->x1A9C = 1.0f;
            pjt->x1A98 = 1.0f;
            ACT *pact = pjt->x1B08;
            svt = 0.0f;
            pjt->tHang = g_clock.t;
            paseg = pjt->x1A94;
            ClearXyz(&pact->v);
            tStart = 0.5f;
            func_0028ECE0(pjt, pjt->x1AC8, pjt->x1B08);
            qword posHand = PosWorld(pjt->x1AA4);
            pjt->x1A60 = QwSub(posHand, func_001B2070(pjt));
            func_001B2430(pjt);
            HandleSplice(pjt->phnd, 5);
            func_0013BD00(pjt->phnd, pjt);
            float radFrame = func_001B2038(pjt);
            float radBack = func_0011E3B8(radFrame + 3.1415927f);
            int nKind = 1;
            if (pjt->phnd != 0)
                nKind = pjt->phnd->nKind;
            switch (nKind)
            {
            case 1:
                func_0024E878(pjt, radFrame);
                pjt->x1A00 = 0;
                break;
            case 2:
                func_0024E878(pjt, radBack);
                pjt->x1A00 = 1;
                break;
            case 0:
                if (__builtin_fabsf(func_0011E3B8(radFrame - pjt->radLeft)) < 1.5707964f)
                {
                    func_0024E878(pjt, radFrame);
                    pjt->x1A00 = 0;
                }
                else
                {
                    func_0024E878(pjt, radBack);
                    pjt->x1A00 = 1;
                }
                break;
            }
            {
                SND *psnd = func_002459F8(pjt->phnd->sfxidHangStart);
                func_00244F08(psnd, pjt);
            }
            ClearXyz((VECTOR *)&pjt->v1A0);
            func_001B0FF0(pjt);
            func_001F47C8(pjt, pjt->phnd->ptn);
        }
        break;
        case 9:
            func_001BFAD0(pjt->x1010, 0);
            fKeep = 1;
            break;
        case 5:
            func_001BDBB0(pjt->xF60, -1);
            break;
        case 8:
            if (pjt->nState < 5)
                grf = (pjt->nState < 3) ? 0 : 7;
            break;
        case 0x12:
            fKeep = 1;
            break;
        case 0xA:
            paseg = pjt->x1C20;
            grfapl = 9;
            tStart = pjt->uGait * paseg->tMax;
            pjt->x1144 = -1;
            break;
        case 0xB:
            VCall(pjt, 102);
            paseg = pjt->x1C28;
            *(qword *)&pjt->v1A0 = D_00317560;
            pjt->x11B8 |= 2;
            grf = 100;
            pjt->x1C2C = 0;
            break;
        case 1:
        {
            GAIT *pgait = 0;
            if (F1108(pjt))
                pgait = func_00173408(pjt->x1108);
            if (pgait == 0)
                pgait = &pjt->gait1C90;
            paseg = pgait->pasegbl;
            grfapl = 9;
            func_00258F28(pgait);
            tStart = pjt->uGait * paseg->tMax;
        }
        break;
        case 0xD:
            VCall(pjt, 102);
            pjt->x11B8 |= 4;
            if (FCanUseGadget(pjt, 0x1C))
            {
                paseg = pjt->x1ABC;
                func_001AFF00(pjt);
                MATRIX3 *pmat = &pjt->matTarget;
                qword qwVel = QwRotateVecRows(*(qword *)pmat->mat[0], *(qword *)pmat->mat[1], *(qword *)pmat->mat[2], QwScale(*(qword *)&pjt->v1A0, VuFloat(-1.0f)));
                SetVelocity(pjt, qwVel);
                func_0024F0B0(pjt);
            }
            else
            {
                paseg = pjt->x1AB8;
                qword posTarget = PosWorld(pjt->x11B4);
                float gZero = 0.0f;
                qword dpos = QwSub(posTarget, PosWorld(pjt));
                func_0024E8E8(pjt, QwScale(dpos, VuFloat(-1.0f)));
                func_0024F0B0(pjt);
                float tLabel = func_001368E0(paseg, 0x2A6);
                MATRIX4 matHand;
                func_00137070(tLabel, gZero, paseg, pjt, pjt->x1AA4->x50, pjt->x50, &matHand, 0);
                tLabel /= paseg->svtMaster;
                qword posHold = PosWorld(pjt->x11B4);
                qword posAim = QwSub(QwAddVelocity(VuFloatBits(tLabel), posHold, GetVelocity(pjt->x11B4)), QwRotateVecV(*(qword *)&matHand.mat[3], &pjt->matTarget));
                *(qword *)&pjt->v1A0 = QwDivide(QwSub(posAim, PosWorld(pjt)), VuFloatBits(tLabel));
                pjt->v1A0.z = gZero;
                SetVelocity(pjt, *(qword *)&pjt->v1A0);
            }
            break;
        case 0xE:
            psm = pjt->x1138;
            func_0028F068(pjt, pjt->x48, 1);
            func_0028F068(pjt, pjt->x4C, 1);
            ClearXyz((VECTOR *)&pjt->v1A0);
            VCall(pjt, 102);
        case 0xF:
            func_0028F068(pjt, pjt->x48, 1);
            func_0028F068(pjt, pjt->x4C, 1);
            ClearXyz((VECTOR *)&pjt->v1A0);
            VCall(pjt, 102);
            break;
        case 0x10:
            func_0028F068(pjt, pjt->x48, 2);
            func_0028F068(pjt, pjt->x4C, 2);
            ClearXyz((VECTOR *)&pjt->v1A0);
            VCall(pjt, 102);
            break;
        case 0x11:
            paseg = pjt->x1E50;
            grfapl = 9;
            VCall(pjt, 102);
            func_0024F3B8(pjt, pjt->phnd, 1);
            pjt->x1120 = QwSub(func_001AFE60(pjt), PosWorld(pjt));
            HandleSplice(pjt->phnd, 5);
            func_0013BD00(pjt->phnd, pjt);
            func_001F47C8(pjt, pjt->phnd->ptn);
            {
                SND *psnd = func_002459F8(pjt->phnd->sfxidHangStart);
                func_00244F08(psnd, pjt);
            }
            break;
        case 0x13:
            grfapl = 9;
            grf = 0x18;
            pjt->x1EC4 = 0.0f;
            pjt->x1EDC = 0.0f;
            pjt->x1ED0 = 1.0f;
            func_00148938(pjt->x1EE8);
            paseg = pjt->x1EE8;
            pjt->x1EEC = 0;
            pjt->x1EF0 = 0;
            ClearXyz((VECTOR *)&pjt->v1A0);
            func_0024F1E8(pjt, 2.0f);
            break;
        case 0x14:
        {
            MATRIX4 mat;
            grfapl = 9;
            int r;
            {
                OBJ *p = D_0038AE90->x18EC;
                VTE *e = &p->vt[37];
                r = ((int (*)(void *, MATRIX4 *))e->fn)(VTHIS(p, e), &mat);
            }
            mat = func_0028EC08(pjt->x44->xA0, pjt->x48->xA0, &mat);
            {
                int n = pjt->xA24;
                VTE *e = &pjt->vt[10];
                ((void (*)(void *, void *, int, int))e->fn)(VTHIS(pjt, e), D_0038AE90, r, 3);
                pjt->xA24 = n;
            }
            SetVelocity(pjt, D_00317560);
            SetAngularVelocity(pjt, D_00317560);
            pjt->x1F00 = func_00130078(pjt, pjt->x48, 1, 8, 2, *(qword *)mat.mat[3]);
            pjt->x1F04 = func_00130078(pjt, pjt->x4C, 1, 8, 2, func_0011D3C0(&mat));
            paseg = pjt->x1F3C;
        }
        break;
        case 0x15:
            fKeep = 1;
            break;
        case 0x16:
        {
            ClearXyz((VECTOR *)&pjt->v1A0);
            grf = 0x18;
            oid = -1;
            func_0024E920(pjt, pjt->x1454);
            {
                VTE *e = &pjt->vt[35];
                ((void (*)(void *, MATRIX3 *))e->fn)(VTHIS(pjt, e), &pjt->matTarget);
            }
            psm = pjt->x1F38;
            VCall(pjt->x168, 54);
            int r = func_001F4A80(pjt);
            pjt->x1F08 = func_0016C608(func_00169BF8(0x28), r, 4, pjt, pjt->x1454);
            func_00169CE0(pjt->x1F08);
        }
        break;
        case 0x17:
            ClearXyz((VECTOR *)&pjt->v1A0);
            break;
        case 0x18:
            func_00279120(pjt->x1F20, pjt);
            ClearXyz((VECTOR *)&pjt->v1A0);
            SetVelocity(pjt, D_00317560);
            SetAngularVelocity(pjt, D_00317560);
            if (pjt->x144C != 0)
            {
                VCall(pjt->x144C, 8);
                func_0023B620(pjt->x144C, 1);
                if (pjt->x144C->x140 != 0)
                {
                    float g = Limit(Evaluate(&D_00322730, pjt->x1F20->x4C), &D_00322740);
                    SetXyz(&pjt->x144C->x140->v, g);
                }
            }
            break;
        }
    }
    if (pjt->jtbs != jtbs)
    {
        switch (jtbs)
        {
        case -1:
            break;
        case 0:
        case 1:
        case 2:
        {
            if (pjt->x113C != 0 && pjt->x113C->paseg == pjt->x1A94)
            {
                fKeep = 1;
            }
            else
            {
                paseg = pjt->x1A94;
                svt = 0.0f;
                tStart = paseg->tMax * 0.5f;
            }
        }
        break;
        case 3:
            psm = pjt->x1A50;
            break;
        case 4:
            psm = pjt->x1C24;
            ClearXyz((VECTOR *)&pjt->v1A0);
            break;
        case 5:
            pjt->x1144 = -1;
            paseg = pjt->x1620;
            ClearXyz((VECTOR *)&pjt->v1A0);
            grfapl = 9;
            break;
        case 6:
            pjt->x210 = 3.0f;
            grf = 0x18;
            break;
        case 7:
            pjt->x210 = 0.08f;
            grf = 0x18;
            func_001B0450(pjt);
            fKeep = 1;
            break;
        case 8:
            paseg = pjt->x1E70;
            grfapl = 9;
            grf = 0x18;
            break;
        case 9:
            if (pjt->x1F20->x27C & 1)
                paseg = pjt->x1E74;
            else
                paseg = pjt->x1E78;
            grf = 0x18;
            break;
        }
    }
    if (jts != pjt->jts)
    {
        pjt->jts = jts;
        pjt->tJts = g_clock.t;
    }
    if (jtbs != pjt->jtbs)
    {
        pjt->jtbs = jtbs;
        pjt->tJtbs = g_clock.t;
    }
    VCall(pjt, 101);
    func_001ADCA0(pjt, grf);
    if (!fKeep)
    {
        if (pjt->x113C != 0)
            func_00137628(&pjt->x113C);
        else if (pjt->x1140 != 0)
            func_0023AC58(&pjt->x1140);
        if (paseg != 0)
        {
            func_00136908(paseg, pjt, tStart, svt, grfapl, &pjt->x113C);
            VCall(pjt->x113C, 1);
        }
        else if (psm != 0)
        {
            pjt->x1140 = func_002399F0(psm, pjt, oid, grfapl, grfRoute);
            VCall(pjt->x1140, 1);
        }
    }
}
