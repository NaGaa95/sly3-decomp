// Step a batch of launch items: each item is sampled at the normalised time of the effect, converted to a matrix and swept against the world; items that hit something are reported, and when every item is finished the owner is told through its hook.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Item { char pad[0x40]; };
struct Obj { char pad0[0x34]; float g34; char pad38[0x90 - 0x38]; float g90; };
struct Self {
    char pad0[0x14]; float start; float duration; Obj *obj;
    char pad20[0xE8 - 0x20]; VTE *hooks;
};
struct SW { char pad[0x3ED0]; qword q3ED0; };
struct CLOCK { float now; };
extern SW D_00475480;
extern CLOCK D_0036BB98;
extern "C" {
void func_002BEC38(void *);
M4 func_0011D6D8(qword pos, M3 *m, float g);
qword func_0018E630(SW *, qword, int, qword);
qword func_0018E728(SW *, qword, int, qword, float);
void func_001C8248(Obj *, qword, M4 *, float, float);
}
struct Params {
    qword pos; M3 m; float g40, g44; char pad48[8];
    Params() { func_002BEC38(this); }
};
union U { qword q; float f[4]; };
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
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
static inline qword FromFloat(float g) { U u; qword q; __asm__("mfc1 %0,%1" : "=r"(q) : "f"(g)); u.q = q; return u.q; }
extern "C" void func_0020C470(Self *self, int count, Item *items)
{
    if (!self->obj) {
        VTE *e = &self->hooks[6];
        ((void (*)(void *, Item *))e->pfn)((char *)self + e->d, items);
        return;
    }
    float t = (D_0036BB98.now - self->start) / self->duration;
    int done = 0;
    for (int i = 0; i < count; i++) {
        Params p;
        VTE *e = &self->hooks[8];
        ((void (*)(void *, Item *, float, Params *))e->pfn)((char *)self + e->d, &items[i], t, &p);
        M4 mat = func_0011D6D8(p.pos, &p.m, p.g44);
        qword w = FromFloat(p.g44 * self->obj->g90);
        qword v = Pack(GetX(mat.r[3]), GetY(mat.r[3]), GetZ(mat.r[3]), GetX(w));
        U r;
        r.q = func_0018E630(&D_00475480, D_00475480.q3ED0, 0xFF, v);
        if (IsZero(r.q)) {
            r.q = func_0018E728(&D_00475480, D_00475480.q3ED0, 0xFF, v, self->obj->g34);
            if (IsZero(r.q))
                done++;
        } else {
            if (p.g40 < 0.0001f) continue;
            if (p.g44 < 0.0001f) continue;
            func_001C8248(self->obj, r.q, &mat, p.g40, p.g40);
        }
    }
    if (done == count) {
        VTE *e = &self->hooks[6];
        ((void (*)(void *))e->pfn)((char *)self + e->d);
    }
}
