// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_0013A1E8.cpp, with the draw loop of the sibling src/leaf/func_00201390.cpp.
// func_0014A6D0: collects the transforms (M4: rotation of the parent, position of the object) of every light in p->xD0's
// list that passes func_001C8610 into a stack array (or the single D_003174C0 when the list is empty), then, per light,
// moves the emitter's sphere by the transform, gets the per-view weights from func_0018E500 and draws every particle batch
// for each view with a weight through the VIF queue D_0036C308 (batch uploads plus the microprogram of p->mode).
// Scope objects (all 1 byte, so the frame is at sp+0 and both guards at sp+1):
//  * CTX: stack frame, inline ctor/dtor calling func_001D2770 / func_001D2798.
//  * S_002BC3B0 (gather branch): its destructor is only DECLARED here. g++ then calls the out-of-line `_$_10S_002BC3B0(this, 2)`
//    with `ori a0,sp,1` like the target; the name is bound to NaGa's src/hand/func_002BC3B0.c by the alias
//    `_$_10S_002BC3B0 = 0x002BC3B0;` in config/symbol_addrs.txt, so this object defines no destructor.
//  * Guard (draw loop): inline dtor calling func_002BC3D8 directly (gives the target's `addiu a0,sp,1`).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[3]; float x30, y30, z30, w30; };
struct XF { M3 mat; qword pos; };
struct VIFS { void *pbMax; void *ab; void *pqwCnt; void *pb; };
struct VTE { short d; short pad; XF *(*pfn)(void *); };
struct VT { VTE a[37]; };
struct LO;
struct EX { int pad[2]; LO **pplo; };
struct LO { char pad[0xC]; VT *pvt; LO *x10; char pad14[0x34 - 0x14]; float g34; char pad38[0xD4 - 0x38]; EX *xD4; char padD8[0x108 - 0xD8]; LO *x108; };
struct OBJ { char pad[0x34]; float g34; char pad38[0xFC - 0x38]; LO *xFC; };
struct BATCH { char abuf[2][0x840]; int i; int c; int pad1088, pad108C; BATCH *pnext; };
struct VIEW;
struct PX {
    char pad0[0x34]; float g34; char pad38[0xD0 - 0x38]; OBJ *xD0; char padD4[0xE0 - 0xD4]; qword centre; float radius;
    char padF4[0x42C - 0xF4]; int mode; char pad430[0x438 - 0x430]; BATCH *pbatch;
};
struct SW { char pad[0x3EB8]; int c3EB8; VIEW *ap3EBC[5]; qword q3ED0; };
struct DQ { int x0; int x4; void *pqw; int padC; };
struct AL { int cb; int align; AL(int c, int a) { cb = c; align = a; } };
extern "C" {
extern SW D_00475480;
extern VIFS D_0036C308;
extern M3 D_00317490;
extern M4 D_003174C0;
extern char D_00000000[];
extern char D_00000398[];
extern char D_00000880[];
void func_001D2770(void *p);
void func_001D2798(void *p, int n);
void func_002BC3D8(void *self, int flags);
int func_0011B0F0(void *pdl);
int func_0011B108(void *pdl);
void *func_001D25B0(const AL &al);
int func_001C8610(LO *plo);
void func_002BA818(void *pv, qword v);
qword func_0011D5C8(M4 *pm, qword v);
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
void func_001746C0(VIFS *p);
void func_001748F8(VIFS *p);
void func_00174828(VIFS *p);
void func_0014AC48(PX *p, VIEW *pview);
void func_0027E4C0(VIFS *p, int upk, int c, void *pvSrc, int iqw);
void func_0027E5A8(VIFS *p, int upk, int c, void *pvSrc, int iqw, void ***pppv);
void func_0027E2C0(VIFS *p, int wl, int cl);
void func_0027E260(VIFS *p, void *pv);
void func_0027E290(VIFS *p);
DQ *func_00209B60(void);
int func_00174FF0(int a, int i);
int func_00174FF8(int a, int b);
void func_0014A6D0(PX *p);
}
struct CTX { char b; CTX() { func_001D2770(this); } ~CTX() { func_001D2798(this, 2); } };
struct S_002BC3B0 { char b; ~S_002BC3B0(); };
struct Guard { char b; ~Guard() { func_002BC3D8(this, 2); } };
union U { qword q; float f[4]; };
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
struct VU_VECTOR {
    qword q;
    VU_VECTOR(float x, float y, float z, float w)
    {
        qword t, s;
        __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
                : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    }
};
static inline int FZero(qword v)
{
    int f;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(f) : "j"(v));
    return ((f & 0xF) ^ 0xF) == 0;
}
static inline XF *Xf(LO *plo) { VTE *e = &plo->pvt->a[36]; return e->pfn((char *)plo + e->d); }
static inline void *PvAllocStack(int cb) { return func_001D25B0(AL(cb, 0x10)); }

extern "C" void func_0014A6D0(PX *p)
{
    CTX frame;
    int cLight;
    M4 *aLight;
    if (p->xD0 != 0 && func_0011B0F0(&p->xD0->xFC) == 0) {
        S_002BC3B0 guard;
        cLight = 0;
        aLight = (M4 *)PvAllocStack(func_0011B108(&p->xD0->xFC) << 6);
        M4 *pl = aLight;
        for (LO *plo = p->xD0->xFC; plo; plo = plo->x108) {
            if (!func_001C8610(plo))
                continue;
            LO **pplo = plo->xD4->pplo;
            qword pos;
            M3 mat;
            if (*pplo) {
                pos = Xf(*pplo)->pos;
                mat = Xf(*pplo)->mat;
            } else {
                pos = Xf(plo)->pos;
                if (plo->x10)
                    mat = Xf(plo->x10)->mat;
                else
                    mat = D_00317490;
            }
            func_002BA818(&pl->x30, pos);
            cLight++;
            pl->r[0] = mat.r[0];
            pl->r[1] = mat.r[1];
            pl->r[2] = mat.r[2];
            pl->w30 = 1.0f;
            ((int *)&pl->r[2])[3] = 0;
            ((int *)&pl->r[1])[3] = 0;
            ((int *)&pl->r[0])[3] = 0;
            pl++;
        }
    } else {
        cLight = 1;
        aLight = &D_003174C0;
    }
    if (cLight == 0) {
        return;
    }
    qword vc = VU_VECTOR(GetX(p->centre), GetY(p->centre), GetZ(p->centre), GetX(VU_FLOAT(p->radius).q)).q;
    for (int i = 0; i < cLight; i++) {
        qword vt = func_0011D5C8(&aLight[i], vc);
        U w;
        w.q = func_0018E500(&D_00475480, D_00475480.q3ED0, 0xFF, vt, p->xD0 ? p->xD0->g34 : p->g34);
        if (FZero(w.q))
            continue;
        for (int j = 0; j < D_00475480.c3EB8; j++) {
            if (w.f[j] == 0.0f)
                continue;
            VIEW *pview = D_00475480.ap3EBC[j];
            Guard guard;
            void *pqw = D_0036C308.pb;
            int cpass = 0;
            func_001746C0(&D_0036C308);
            for (BATCH *pb = p->pbatch; pb; pb = pb->pnext) {
                char *pbuf = pb->abuf[pb->i];
                if (cpass < 2) {
                    cpass++;
                    func_0014AC48(p, pview);
                    func_0027E4C0(&D_0036C308, 0xC, 4, &aLight[i], 7);
                }
                unsigned short as[4];
                as[0] = 0x34;
                as[1] = pb->c * 10 + 0x34;
                as[2] = pb->c;
                as[3] = 0x1000;
                func_0027E4C0(&D_0036C308, 0xD, 1, as, 0);
                func_0027E2C0(&D_0036C308, 1, 10);
                if (p->mode == 1)
                    func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf + 0x2B0, as[0] + 1, 0);
                func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf + 0x560, as[0] + 2, 0);
                func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf, as[0] + 3, 0);
                func_0027E2C0(&D_0036C308, 1, 1);
                switch (p->mode) {
                case 0:
                    func_0027E260(&D_0036C308, D_00000000);
                    break;
                case 1:
                    func_0027E260(&D_0036C308, D_00000398);
                    break;
                case 2:
                    func_0027E260(&D_0036C308, D_00000880);
                    break;
                }
                func_0027E290(&D_0036C308);
            }
            func_001748F8(&D_0036C308);
            func_00174828(&D_0036C308);
            DQ *pq = func_00209B60();
            pq->x0 = func_00174FF8(0xB, func_00174FF0(5, j));
            pq->x4 = 0;
            pq->pqw = pqw;
        }
    }
}
