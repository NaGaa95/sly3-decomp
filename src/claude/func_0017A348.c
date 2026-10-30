// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_0015C690.c (EMITTER/EMITB offsets shifted, flag bits renumbered, EMITP shrank to 16 bytes).
typedef int qword __attribute__((mode(TI)));
typedef struct EMITP { int x0; int x4; int x8; int xC; } EMITP;
typedef struct XF4 { qword v; } XF4;
typedef struct X4 { char pad[0xE4]; XF4 *p; } X4;
typedef struct FRM { qword pos; qword m[3]; } FRM;
typedef struct EMITB {
    int x0; int x4; EMITP *pemitp; int xC; int x10; int x14; int x18; FRM *pfrm; int pad20[4];
    union { qword v; qword *pm; EMITP *pemitp; struct { char pad[0x20]; qword v; } *pq; } u30;
    qword v40;
    float g50, g54;
    char pad58[0xD4 - 0x58];
    float gD4, gD8;
    int xDC;
    qword vE0[2];
} EMITB;
typedef struct SND { int id; float g4, g8, gC, g10; } SND;
typedef struct EMITTER { char pad[0xD4]; EMITB *pemitb; int xD8, xDC; SND *psnd; float gE4, gE8; int xEC; int xF0; int xF4; } EMITTER;
typedef struct EMITO { int grf; int x4; float g8; float gC; qword v10; qword v20; int x30; int x34; } EMITO;
typedef struct EMITR { int *p104; int *p100; EMITTER *p; } EMITR;

/* rodata LM at 0x003212F8 (not in symbol_addrs) */
static const float D_003212F8[2] = { 0.5f, 2.0f };
extern float func_0011E940(float lo, float hi);
extern float func_0011EE68(void *p, float g);
typedef union V4 { qword q; float a[4]; } V4;
extern V4 func_002BA7E8(float g);
extern V4 func_002BA808(qword *pv);
extern qword func_002BA828(qword a, qword b);
extern void func_002BA818(qword *pv, qword a);
extern void func_00179B20(int c, EMITB *pb, EMITR *pr);
extern qword func_001C9428(int x, int y, qword v);
extern void *func_002459F8(int id);
extern void func_00244F08(void *p, void *pso);
extern void func_00245000(void *p, qword v);
extern void func_00245100(void *p, float a, float b);
extern void func_00244E08(void *p, float g);
extern void func_00244ED0(void *p, float g);

void func_0017A348(EMITTER *p, EMITO *po)
{
    EMITP emitp;
    EMITB b;
    EMITR r;
    EMITR *pr;
    int c;
    V4 pos;
    V4 h;

    emitp = *p->pemitb->pemitp;
    b = *p->pemitb;
    b.pemitp = &emitp;
    if (po->grf & 0x40)
        c = po->x34;
    else
        c = (int)func_0011E940(p->gE4, p->gE8);
    if (po->grf & 1)
        emitp.x0 = po->x4;
    if (po->grf & 2)
        b.v40 = po->v10;
    if (po->grf & 4) {
        b.u30.v = po->v20;
        b.x10 = 0;
    } else if (po->grf & 0x20) {
        b.pfrm = (FRM *)po->x30;
    }
    if ((po->grf & 8) && b.x4 == 0) {
        float g;
        float gs;
        int n;
        if (po->g8 == 0.0f)
            g = po->gC * 0.01f;
        else
            g = po->g8;
        if (g < 1.0f)
            c = (int)(c * g);
        else
            c = (int)(c / g);
        n = (int)p->gE8 / 2;
        if (!(n < c))
            c = n;
        gs = func_0011EE68((void *)D_003212F8, g);
        b.g50 *= gs;
        b.g54 *= gs;
        { float h = 0.5f; g = (h < g) ? g : h; }
        func_002BA818(b.vE0, func_002BA828(func_002BA7E8(g).q, func_002BA808(b.vE0).q));
    }
    if (b.x4 == 1) {
        if (po->grf & 0x10)
            b.gD8 = b.gD4 = po->g8;
    }
    if (p->xEC) {
        r.p104 = &p->xF4;
        r.p100 = &p->xF0;
        r.p = p;
        pr = &r;
    } else {
        pr = 0;
    }
    if (emitp.x0 == 0 && b.x10 != 2 && !(po->grf & 0x28))
        emitp.x0 = (int)p;
    func_00179B20(c, &b, pr);
    if (p->psnd) {
        void *ps;
        switch (b.x10) {
        case 0:
            pos.q = b.u30.v;
            break;
        case 1: {
            float half = 0.5f;
            {
                register qword hv __asm__("vf1"); /* pin: target keeps the 0.5 splat in vf1 */
                __asm__("qmtc2.ni %1, %0" : "=j"(hv) : "r"(half));
                h.q = hv;
                {
                    qword *pm = b.u30.pm;
                    qword m1 = pm[1];
                    qword m0 = pm[0];
                    qword r;
                    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(m0), "j"(m1), "0"(hv));
                    pos.q = r;
                }
            }
            break;
        }
        case 2:
            pos.q = ((X4 *)b.pemitp->x4)->p->v;
            break;
        case 3:
            pos.q = b.u30.pq->v;
            break;
        }
        if (b.pfrm) {
            FRM *pf = b.pfrm;
            qword *pm = pf->m;
            qword v = pos.q;
            qword m0 = pm[0];
            qword m1 = pm[1];
            qword m2 = pm[2];
            __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "0"(v), "j"(m0), "j"(m1), "j"(m2));
            {
            qword t = pf->pos;
            __asm__("vadd.xyzw %0, %0, %1" : "=j"(v) : "j"(t), "0"(v));
            }
            pos.q = v;
        }
        pos.q = func_001C9428(emitp.x0, 0, pos.q);
        ps = func_002459F8(p->psnd->id);
        func_00244F08(ps, 0);
        func_00245000(ps, pos.q);
        func_00245100(ps, p->psnd->g4, p->psnd->g8);
        func_00244E08(ps, p->psnd->gC);
        func_00244ED0(ps, p->psnd->g10);
    }
}
