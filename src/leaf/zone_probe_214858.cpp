// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Self {
    char pad0[0xC]; VTE *pvt; char pad10[0x2C - 0x10]; unsigned char b2C; char pad2D[0x34 - 0x2D]; float g34;
    char pad38[0x220 - 0x38]; float g220;
    char pad224[0x458 - 0x224]; float lastHit;
};
struct SW { char pad[0x3ED0]; qword q3ED0; };
struct CLOCK { float now; };
extern "C" {
extern SW D_00475480;
extern CLOCK D_0036BB98;
void func_0023CC40(Self *self);
qword func_0018E500(SW *psw, qword q, int k, qword v, float g);
}
union U { qword q; float f[4]; };
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline M4 *Matrix(void *pv) { Self *p = (Self *)pv; VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3
	mfc1 %1,%4
	pextlw %0,%1,%0
	mfc1 %1,%5
	mfc1 %2,%6
	pextlw %1,%2,%1
	pcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    u.q = q;
    return u.q;
}
static inline int IsZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return ((mac & 0xF) ^ 0xF) == 0;
}
extern "C" void func_00214858(Self *self)
{
    U hit;
    func_0023CC40(self);
    qword pos = Matrix(self)->r[3];
    qword v = Pack(GetX(pos), GetY(pos), GetZ(pos), GetX(VU_FLOAT(self->g220).q));
    hit.q = func_0018E500(&D_00475480, D_00475480.q3ED0, self->b2C, v, self->g34);
    if (!IsZero(hit.q))
        self->lastHit = D_0036BB98.now;
}
