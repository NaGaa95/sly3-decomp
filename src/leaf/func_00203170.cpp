// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Visibility query of a tracked object: depending on its mode (0..3) returns 3/2/1/0 after testing the placement of the object (or of every
// object of its list) against the world with func_0018E728.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct Placement { char pad0[0x30]; qword position; };
struct Obj;
struct ObjList { Obj *first; };
struct Obj {
    char pad0[0xC]; VTE *vt; int active; char pad14[0x34 - 0x14]; float g34; char pad38[0xD8 - 0x38]; int mode;
    char padDC[0xF4 - 0xDC]; ObjList *list; Obj *next;
};
struct Probe { char pad0[0x508]; int x508; char pad50C[0x19E0 - 0x50C]; int x19E0; };
struct Self { char pad0[0x10]; Obj *obj; };
struct SW { char pad[0x3ED0]; qword q3ED0; };
extern SW D_00475480;
extern "C" {
int func_001C8610(Obj *);
Probe *func_001F4AD0(SW *, int);
int func_0013B500(Probe *, int);
qword func_0018E728(SW *, float, qword, int, qword);
}
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
static inline qword Position(Obj *o)
{
    VTE *e = &o->vt[36];
    return ((Placement *(*)(void *))e->pfn)((char *)o + e->d)->position;
}
extern "C" int func_00203170(Self *self)
{
    Obj *obj = self->obj;
    switch (obj->mode) {
    case 3: {
        if (!func_001C8610(obj))
            return 2;
        Probe *probe = func_001F4AD0(&D_00475480, 0);
        if (!probe)
            return 3;
        if (func_0013B500(probe, 0x45))
            return 0;
        if (!func_0013B500(probe, 0x34))
            return 3;
        if (probe->x19E0 == 8 && probe->x508 == probe->x19E0)
            return 0;
        return 3;
    }
    case 0:
        return 3;
    case 1: {
        if (!func_001C8610(obj))
            return 2;
        if (!self->obj->active)
            return 3;
        qword q = Position(self->obj);
        qword w = FromFloat(0.0f);
        qword v = Pack(GetX(q), GetY(q), GetZ(q), GetX(w));
        int result = 1;
        if (IsZero(func_0018E728(&D_00475480, self->obj->g34, D_00475480.q3ED0, 0xFF, v)))
            result = 0;
        return result;
    }
    case 2: {
        int flags = 2;
        for (Obj *o = obj->list->first; o; o = o->next) {
            if (!o->active) {
                flags |= 1;
                continue;
            }
            flags &= ~2;
            qword q = Position(o);
            qword w = FromFloat(0.0f);
            qword v = Pack(GetX(q), GetY(q), GetZ(q), GetX(w));
            if (!IsZero(func_0018E728(&D_00475480, o->g34, D_00475480.q3ED0, 0xFF, v)))
                return 1;
        }
        return flags;
    }
    default:
        return 2;
    }
}
