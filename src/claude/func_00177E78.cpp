// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// UpdateEmitter. Sly 2 reference: src/hand/UpdateEmitter__FP7EMITTERf.cpp.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
struct VTE { short d; short pad; qword *(*pfn)(void *); };
struct EMITO { void *palo; int f4; };
struct EMITB { int pad0; int f4; EMITO *pemito; };
struct EMITTER {
    char pad0[0xC]; VTE *vt; int x10; char pad14[0x34 - 0x14]; float g34;
    char pad38[0xD0 - 0x38]; int fChanged; EMITB *pemitb; char padD8[0xE0 - 0xD8]; int k; int c;
    float gE8, gEC, gF0, gF4; int xF8; int dlFC; char pad100[0x108 - 0x100]; EMITTER *pNext; char pad10C[4];
    float g110, g114, g118; char pad11C[4]; float g120; char pad124[4]; void *x128; void *x12C;
};
struct EMITX { void **ppprg; void **ppripg; EMITTER *pemitter; };
class SCOPE;
extern "C" void func_002BC3B0(SCOPE *, int);
class SCOPE {
    int m_a[4];
public:
    SCOPE() {}
    ~SCOPE() { func_002BC3B0(this, 2); }
};
extern "C" {
extern CLOCK g_clock;
extern char D_00475480[];
void func_001781B8(EMITTER *p);
void func_001C8168(EMITTER *p);
void *func_00165B28(void *p);
int func_0011B0F0(int *pdl);
int func_001C8610(EMITTER *p);
int func_00168048(void *p, qword pos, float r, int n);
int func_00178170(EMITTER *p);
float func_0011E940(float gMin, float gMax);
void func_00178138(EMITTER *p, float dt);
void *memset(void *pv, int b, unsigned int cb);
void func_00179B20(int c, EMITB *pemitb, EMITX *px);
void func_00177BF0(EMITTER *p);
}
static inline qword Pos(EMITTER *p)
{
    VTE *e = &p->vt[36];
    return e->pfn((char *)p + e->d)[3];
}
extern "C" void func_00177E78(EMITTER *p)
{
    if (p->fChanged)
        func_001781B8(p);
    func_001C8168(p);
    if (p->xF8 != -1)
        return;
    void *pv = func_00165B28(D_00475480);
    if (!func_0011B0F0(&p->dlFC)) {
        SCOPE scope;
        EMITTER *pe;
        for (pe = *(EMITTER **)&p->dlFC; pe; pe = pe->pNext) {
            if (!func_001C8610(pe))
                continue;
            if (!pe->x10)
                goto LActive;
            if (func_00168048(pv, Pos(pe), pe->g34, 0))
                goto LActive;
        }
        return;
    } else if (p->x10) {
        if (!func_00168048(pv, Pos(p), p->g34, 0))
            return;
    }
LActive:
    if (func_00178170(p))
        return;

    int c = 0;
    switch (p->k) {
    case 0: {
        c = (int)p->g110;
        int cLeft = p->c;
        if (cLeft >= 0) {
            if (cLeft <= c)
                c = cLeft;
            p->c = cLeft - c;
        }
        func_00178138(p, func_0011E940(p->gF0, p->gF4));
        p->g110 = func_0011E940(p->gE8, p->gEC);
        break;
    }
    case 1: {
        float g = p->g120 + p->g110 * g_clock.dt;
        c = (int)g;
        p->g120 = g - (float)c;
        if (c != 0) {
            int cLeft = p->c;
            if (cLeft >= 0) {
                if (cLeft <= c)
                    c = cLeft;
                p->c = cLeft - c;
            }
        }
        break;
    }
    }

    if (c) {
        int unused[4];
        EMITX x;
        memset(&x, 0, sizeof(x));
        x.pemitter = p;
        x.ppprg = &p->x12C;
        x.ppripg = &p->x128;
        EMITO *pemito = p->pemitb->pemito;
        void *palo = pemito->palo;
        if (!palo && !pemito->f4)
            pemito->palo = p;
        func_00179B20(c, p->pemitb, &x);
        p->pemitb->pemito->palo = palo;
    }

    if (g_clock.t >= p->g118) {
        p->g110 = func_0011E940(p->gE8, p->gEC);
        p->g118 = g_clock.t + p->g114;
    }
    func_00177BF0(p);
}
