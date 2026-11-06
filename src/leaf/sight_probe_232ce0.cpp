// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00232CE0: line-of-sight check of a tracked object. If the target (self->p13C) position is inside the probe region, test the segment
// from this object (w = 10.0) against the scene with func_0018E630; when that reports a hit set, trace the segment through the collision
// scene (func_0025CF18/func_00165000) and, when nothing blocks it, remember the target position (+0x270) and notify (func_00232E88).
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct OBJ { char pad[0xC]; VTE *pvt; };
struct SELF {
    char pad0[0xC]; VTE *pvt; char pad10[0xDC - 0x10]; int xDC; char padE0[0x13C - 0xE0]; OBJ *p13C; char pad140[0x148 - 0x140];
    void *region; char pad14C[0x270 - 0x14C]; qword q270;
};
struct SW { char pad[0x3ED0]; qword q3ED0; };
class CFrame { public: CFrame(); ~CFrame(); };
extern "C" {
extern SW D_00475480;
int func_0027F258(void *region, qword pos);
qword func_0018E630(SW *psw, qword q, int k, qword v);
int func_00232C58();
void func_0025CF18(SW *pg, qword a, qword b, int (*pfn)(), int c, int *pn0, int *pn1);
void *func_00165000(int n, qword a, qword b, int n0, int n1, void *phit);
void func_00232E88(SELF *self);
void func_00232CE0(SELF *self);
}
union U { qword q; float f[4]; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); } };
static inline M4 *Matrix(void *pv) { OBJ *p = (OBJ *)pv; VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
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
void func_00232CE0(SELF *self)
{
    U w;
    qword pos = Matrix(self->p13C)->r[3];
    if (!func_0027F258(self->region, pos))
        return;
    qword here = Matrix(self)->r[3];
    qword v = VU_VECTOR(GetX(here), GetY(here), GetZ(here), GetX(VU_FLOAT(10.0f).q)).q;
    w.q = func_0018E630(&D_00475480, D_00475480.q3ED0, 0xFF, v);
    if (!FZero(w.q)) {
        CFrame frame;
        int n0, n1;
        func_0025CF18(&D_00475480, Matrix(self)->r[3], pos, func_00232C58, self->xDC, &n0, &n1);
        if (!func_00165000(0, Matrix(self)->r[3], pos, n0, n1, 0)) {
            self->q270 = pos;
            func_00232E88(self);
        }
    }
}
