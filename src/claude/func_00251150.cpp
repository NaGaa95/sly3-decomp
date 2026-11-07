// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct BITS { unsigned char ab[16]; };
struct XF { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; XF *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct LO { char pad[0xC]; VT *pvt; };
struct ENT { char pad[8]; int n8; };
struct LINK { char pad[0xC]; LO *pC; };
struct SO {
    char pad[0xC]; VT *pvt; char pad10[0x2F4 - 0x10]; BITS grf; char pad304[0x3D8 - 0x304]; LINK *p3D8;
    char pad3DC[0x10D0 - 0x3DC]; void *p10D0; char pad10D4[0x11BC - 0x10D4]; int n11BC; int n11C0;
};
extern "C" {
extern BITS D_00475440, D_00475450;
extern void *D_00370AC0;
void func_0016FCF8(void *p);
int func_00170500(void *p, void *q);
ENT *func_00170528(void *owner, void *link);
void func_002566F0(LINK *p, int n);
void func_00251150(SO *p);
}
static inline BITS operator&(const BITS &a, const BITS &b)
{
    BITS r;
    for (int i = 0; i < 16; i++) r.ab[i] = a.ab[i] & b.ab[i];
    return r;
}
static inline int operator!=(const BITS &a, const BITS &b)
{
    for (int i = 0; i < 16; i++)
        if (a.ab[i] != b.ab[i]) return 1;
    return 0;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float LenXY(qword d)
{
    qword t; float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_00251150(SO *p)
{
    if ((p->grf & D_00475450) != D_00475440) return;
    func_0016FCF8(p->p10D0);
    if (p->n11C0 == 1 && p->n11BC && D_00370AC0) {
        if (!func_00170500(p->p10D0, D_00370AC0)) p->n11BC = 0;
    }
    if (!p->p3D8) return;
    ENT *e = func_00170528(p->p10D0, p->p3D8->pC);
    if (!e) return;
    switch (e->n8) {
    case 1:
        func_002566F0(p->p3D8, 1);
        break;
    case 2: {
        LO *o = p->p3D8->pC;
        qword a = o->pvt->e120.pfn((char *)o + o->pvt->e120.d)->pos;
        qword d = Sub(a, p->pvt->e120.pfn((char *)p + p->pvt->e120.d)->pos);
        int f = 0;
        if (LenXY(d) < 1000.0f) {
            float z = GetZ(d);
            if (__builtin_fabsf(z) < 250.0f) f = 1;
        }
        if (f) func_002566F0(p->p3D8, 2);
        break;
    }
    }
}
