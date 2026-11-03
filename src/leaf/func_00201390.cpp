// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Draws the particle batches of an emitter once per transform of an array (light-weighted passes): the emitter's sphere is moved by each
// transform, the scene returns up to four per-light weights for it, and every light slot with a weight is drawn through the VIF queue
// (batch uploads plus the microprogram of the emitter's draw mode) and queued with its sort flags.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VIFS { void *pbMax; void *ab; void *pqwCnt; void *pb; };
struct OBJ { char pad[0x10]; OBJ *x10; char pad14[0x34 - 0x14]; float g34; };
struct Shape { char pad0[0x18]; int k18; char pad1C[8]; int k24; };
struct Kind { char pad0[0x1C]; Shape *shape; };
struct BATCH {
    char abuf[2][0x840];
    int i;
    int c;
    int pad1088, pad108C;
    BATCH *pnext;
};
struct PX {
    OBJ *owner;
    Kind *kind;
    char pad8[0x2C - 8];
    float radius;
    qword centre;
    char pad40[0x50 - 0x40];
    BATCH *pbatch;
};
struct VIEW { char pad[1]; };
struct SW { char pad[0x3EB8]; int c3EB8; VIEW *ap3EBC[5]; qword q3ED0; };
struct DQ { int x0; int pad4; void *pqw; int padC; };
extern "C" {
extern SW D_00475480;
extern VIFS D_0036C308;
extern char D_00000000[];
extern char D_00000398[];
extern char D_00000880[];
void func_002BC3D8(void *self, int flags);
qword func_0011D5C8(M4 *pm, qword v);
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
void func_001746C0(VIFS *p);
void func_001748F8(VIFS *p);
void func_00174828(VIFS *p);
void func_00201C18(PX *p, VIEW *pview, int k);
void func_0027E4C0(VIFS *p, int upk, int c, void *pvSrc, int iqw);
void func_0027E5A8(VIFS *p, int upk, int c, void *pvSrc, int iqw, void ***pppv);
void func_0027E2C0(VIFS *p, int wl, int cl);
void func_0027E260(VIFS *p, void *pv);
void func_0027E290(VIFS *p);
DQ *func_00209B60(void);
int func_00174FF0(int a, int i);
int func_00174FF8(int a, int b);
void func_00201390(PX *p, int cm, M4 *am);
}
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
static inline int Flags(int a, int b, int i) { return func_00174FF8(b, func_00174FF0(a, i)); }

extern "C" void func_00201390(PX *p, int cm, M4 *am)
{
    if (!p->pbatch)
        return;
    Shape *pshape = p->kind->shape;
    float w4 = GetX(VU_FLOAT(p->radius).q);
    qword vc = VU_VECTOR(GetX(p->centre), GetY(p->centre), GetZ(p->centre), w4).q;
    int mode = pshape->k24;
    float gSize = p->owner->x10->g34;
    int kLo, kHi;
    if (pshape->k18) {
        kLo = 0xC;
        kHi = 0xD;
    } else {
        kLo = 0xB;
        kHi = 0xB;
    }
    for (int i = 0; i < cm; i++) {
        qword vt = func_0011D5C8(&am[i], vc);
        U w;
        w.q = func_0018E500(&D_00475480, D_00475480.q3ED0, 0xFF, vt, gSize);
        if (FZero(w.q))
            continue;
        for (int j = 0; j < D_00475480.c3EB8; j++) {
            VIEW *pview = D_00475480.ap3EBC[j];
            if (w.f[j] == 0.0f)
                continue;
            for (int k = kLo; k <= kHi; k++) {
                Guard guard;
                void *pqw = D_0036C308.pb;
                int cpass = 0;
                func_001746C0(&D_0036C308);
                for (BATCH *pb = p->pbatch; pb; pb = pb->pnext) {
                    char *pbuf = pb->abuf[pb->i];
                    if (cpass < 2) {
                        cpass++;
                        func_00201C18(p, pview, k);
                        func_0027E4C0(&D_0036C308, 0xC, 4, &am[i], 7);
                    }
                    unsigned short as[4];
                    as[0] = 0x34;
                    as[1] = pb->c * 10 + 0x34;
                    as[2] = pb->c;
                    as[3] = (int)(w.f[j] * 4096.0f);
                    func_0027E4C0(&D_0036C308, 0xD, 1, as, 0);
                    func_0027E2C0(&D_0036C308, 1, 10);
                    if (mode == 1)
                        func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf + 0x2B0, as[0] + 1, 0);
                    func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf + 0x560, as[0] + 2, 0);
                    func_0027E5A8(&D_0036C308, 0xC, pb->c, pbuf, as[0] + 3, 0);
                    func_0027E2C0(&D_0036C308, 1, 1);
                    switch (mode) {
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
                pq->x0 = Flags(5, k, j);
                pq->pqw = pqw;
            }
        }
    }
}
