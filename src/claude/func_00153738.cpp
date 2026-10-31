// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00153738: message handler, ported from Sly 2 func_00140F90 (msg ids +1, offsets moved). Owns jump table 0x320560.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct VT { VTE a[128]; };
#define F(T, p, off) (*(T *)((char *)(p) + (off)))
#define VT_OF(p) F(VT *, p, 0xC)
#define VCALL0(p, n) ((void (*)(void *))VT_OF(p)->a[n].pfn)((char *)(p) + VT_OF(p)->a[n].d)
struct SO { char pad[0x18]; void *p18; };
struct MSG { SO *pso; float g; int k; };
struct MSGB { void *p0; void *p4; };
struct ENT { void *po; int x4; };
struct G;
extern "C" {
extern G D_00475480;
extern qword D_00317560;
void func_0013BD88(void *pv, void *p);
void func_00137688(void *p);
void func_001C8FB0(void *a, void *b);
void func_001C2E78(void *p);
void func_002734E8(void *p, int n);
qword func_0024F278(void *p, SO *pso, float g);
void func_00153EA0(void *p, int n);
void func_002730D8(void *p);
int func_0013B500(void *p, int n);
int func_00277588(void *p);
void func_002775B8(void *p);
void func_00137628(void *p);
void func_00154460(void *p, int n);
void func_00137588(void *pa, void *p, float g, int n, float h, void *pb);
void func_001E4A20(void *p, int n);
void func_001C01A8(G *p, int n);
void func_00208D50(void *p, void *q);
void func_00138B68(void *p, float g);
void func_002091B0(void *p, void *q);
void func_0013A770(void *p, int msg, void *pv);
void func_00238610(void *p, int msg, void *pv);
void func_001F4278(void *p, int msg, void *pv);
void func_00153738(void *p, int msg, void *pv);
}
struct VU_FLOAT2 { qword q; VU_FLOAT2(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
static inline qword Scale2(VU_FLOAT2 s, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword Scale1(qword s, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static inline qword Xform(const qword *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=&j"(r) : "j"(m[0]), "j"(m[1]), "j"(m[2]), "j"(v));
    return r;
}
static inline qword Mul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }

void func_00153738(void *p, int msg, void *pv)
{
    void *pc = F(void *, p, 0x1108);
    if (pc)
        VCALL0(pc, 5);
    switch (msg) {
    case 5:
        if (pv == F(void *, p, 0x113C) ||
            (F(void *, p, 0x1140) != 0 && pv == F(void *, F(void *, p, 0x1140), 0x30))) {
            F(int, p, 0x1144) = -1;
            if ((unsigned)(F(int, p, 0xE44) - 9) < 5) {
                func_001C2E78((char *)p + 0xE40);
            } else {
                switch (F(int, p, 0x1294)) {
                case 5:
                case 6:
                    func_002734E8((char *)p + 0x1290, 4);
                    break;
                case 1:
                case 2:
                    func_002734E8((char *)p + 0x1290, 0);
                    break;
                }
            }
        }
        break;
    case 4:
        if (pv == F(void *, p, 0x1094)) {
            if (F(int, p, 0x1014) != -1) {
                void *pa = F(void *, p, 0x1AA8);
                VCALL0(pa, 8);
                func_001C8FB0(F(void *, p, 0x1AA8), F(void *, p, 0x1AA0));
                pa = F(void *, p, 0x1AA0);
                VCALL0(pa, 9);
                func_00137688((char *)p + 0x1094);
            }
        }
        break;
    case 10: {
        MSG *pmsg = (MSG *)pv;
        if (pmsg->pso->p18 != p)
            break;
        switch (pmsg->k) {
        case 0x17F: {
            VECTOR s; qword r;
            qword v = func_0024F278(p, pmsg->pso, pmsg->g);
            qword sv;
            __asm__("qmtc2.ni %1, %0" : "=j"(sv) : "r"(-1.0f));
            F(qword, p, 0x1A0) = Scale1(sv, v);
            *(qword *)&s = sv;
            r = Xform(&F(qword, p, 0x1C0), v);
            void *pt = F(void *, p, 0x438);
            qword o;
            if (pt) {
                qword q = F(qword, p, 0x440);
                o = Mul(q, ((qword (*)(void *))VT_OF(pt)->a[38].pfn)((char *)pt + VT_OF(pt)->a[38].d));
            } else {
                o = D_00317560;
            }
            ((void (*)(void *, qword))VT_OF(p)->a[40].pfn)((char *)p + VT_OF(p)->a[40].d, Add(r, o));
            break;
        }
        case 0x182:
            func_00153EA0(p, 1);
            break;
        case 0x183:
            func_00153EA0(p, 0);
            break;
        case 0x2E8:
            if (F(int, p, 0x1294) != -1)
                func_002730D8((char *)p + 0x1290);
            break;
        case 0x2E9:
            if (F(int, p, 0x508) == 0xB) {
                void *po;
                int n;
                if (F(void *, p, 0x514) != 0 && func_0013B500(F(void *, p, 0x514), 0x71)) {
                    po = F(void *, p, 0x514);
                    if (func_00277588(po))
                        func_002775B8(po);
                }
                n = F(int, p, 0x9FC);
                if (F(void *, p, 0x13F4) != 0) {
                    if (F(int, p, 0x13FC) == n) {
                        func_00137628((char *)p + 0x13F8);
                        F(int, p, 0x13FC) = -1;
                    } else {
                        func_00154460(p, n);
                        func_00137588(F(void *, p, 0x13F4), p, 0.0f, 8, 1.0f, (char *)p + 0x13F8);
                        F(int, p, 0x13FC) = F(int, p, 0x9FC);
                    }
                } else if (n != -1) {
                    func_00154460(p, n);
                    switch (F(int, p, 0x9FC)) {
                    case 0x16:
                        func_001E4A20(p, 1);
                        break;
                    case 0x14:
                        func_001C01A8(&D_00475480, 0x14);
                        break;
                    }
                }
                F(void *, p, 0x13F4) = 0;
                F(int, p, 0x9FC) = -1;
            }
            break;
        case 0x1F6:
            if (F(int, p, 0x508) == 0xC)
                func_00208D50((char *)p + 0x940, F(void *, p, 0x514));
            break;
        case 0x1F5:
            if (F(int, p, 0x508) == 0xC) {
                func_00138B68(F(void *, p, 0x113C), 1.0f);
                func_002091B0((char *)p + 0x940, F(void *, p, 0x514));
            }
            break;
        case 0x32B:
            if (F(int, p, 0xE44) >= 9)
                VCALL0(p, 103);
            break;
        }
        break;
    }
    case 6: {
        MSGB *pm = (MSGB *)pv;
        if (pm->p4 == p) {
            int i;
            F(void *, p, 0x1164) = pm->p0;
            for (i = 0; i < F(int, p, 0x116C); i++) {
                void *po = F(ENT *, p, 0x1168)[i].po;
                VCALL0(po, 8);
                F(ENT *, p, 0x1168)[i].x4 = 0;
            }
        }
        break;
    }
    case 7: {
        MSGB *pm = (MSGB *)pv;
        if (pm->p4 == p && pm->p0 == F(void *, p, 0x1164)) {
            int i;
            F(void *, p, 0x1164) = 0;
            for (i = 0; i < F(int, p, 0x116C); i++) {
                void *po = F(ENT *, p, 0x1168)[i].po;
                VCALL0(po, 9);
            }
        }
        break;
    }
    case 1:
        if (F(int, p, 0x508) == 0xB && F(void *, p, 0x514) == pv) {
            func_0013BD88(pv, p);
            F(void *, p, 0x514) = 0;
        }
        break;
    case 12:
        if (((MSGB *)pv)->p4 == p) {
            func_00137628((char *)p + 0x13F8);
            F(int, p, 0x13FC) = -1;
        }
        break;
    }
    func_0013A770((char *)p + 0x10D0, msg, pv);
    func_00238610((char *)p + 0x29C, msg, pv);
    func_001F4278(p, msg, pv);
}
