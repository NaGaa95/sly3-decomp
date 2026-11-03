// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Nearest usable point on the actor's probe paths: walks the entries of self, samples every path at 2000 unit steps
// (at least one sample), keeps the closest sample in front of the actor and returns its entry with the point, a basis
// turned to the path tangent and a side flag.
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *(*call)(void *); };
struct Matrix { unsigned char opaque00[0x30]; qword position; };
struct Guard { int storage[4]; };
union U { qword q; float f[4]; };
struct M3 { qword r0, r1, r2; };
struct Obj {
    unsigned char pad0[0xC]; Method *methods;
    unsigned char pad10[0x28 - 0x10]; unsigned long flags;
};
struct Entry { int pad0; Obj *path; int skip; };
struct Self { unsigned char pad0[0x40]; int count; Entry *entries; };
extern "C" {
extern float D_00325E28;
extern qword D_00317550;
void func_001D2770(Guard *);
void func_001D2798(Guard *, int);
void *func_001F4A80(Obj *);
void func_0022EA88(void *path, qword point, int a, qword *closest, int b, int c, float *param);
float func_0022DFD8(void *path);
void func_0022E330(void *path, qword *point, qword *tangent, float s);
int func_00167F60(void *target, qword position, qword extent);
qword func_001C9428(void *, Obj *, qword);
float func_001205C8(qword);
M3 *func_0011C8C0(M3 *, float, qword);
}
union QwordBox { qword q; float f; };
static inline qword BcG(float f) { QwordBox u; qword r; __asm__("mfc1 %0,%1" : "=r"(r) : "f"(f)); u.q = r; return r; }
#define MATRIX(o) ((Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float X(qword a) { float r; __asm__("mtc1 %1,%0" : "=f"(r) : "r"(a), "j"(a)); return r; }
static inline float Xr(qword a) { float r; __asm__("mtc1 %1,%0" : "=f"(r) : "r"(a)); return r; }
static inline float Y(qword a) { float r; __asm__("prot3w %0,%1" : "=r"(r) : "r"(a)); return r; }
static inline qword Root(qword a) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(a)); return r; }
static inline float LengthXY(qword a)
{
    qword r;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(a));
    return X(Root(r));
}
static inline int Max(int a, int b) { return a < b ? b : a; }
extern "C" Entry *func_0021AF38(Self *self, Obj *actor, qword *outPoint, M3 *outBasis, int *outFlag)
{
    Guard guard;
    U bestPoint;
    M3 bestBasis;
    U closest, point, tangent;
    float param;
    func_001D2770(&guard);
    int flag = 0;
    Entry *result = 0;
    float best = D_00325E28;
    void *hero = func_001F4A80(actor);
    for (int i = 0; i < self->count; i++) {
        Entry *e = &self->entries[i];
        Obj *path = e->path;
        if (e->skip || !path) continue;
        int flagged = (path->flags & (1UL << 56)) != 0;
        if (!flagged) continue;
        func_0022EA88(path, MATRIX(actor)->position, 0, &closest.q, 0, 0, &param);
        if (40000.0f < LengthXY(Sub(MATRIX(actor)->position, closest.q))) continue;
        int n = Max(1, (int)(func_0022DFD8(path) * 0.0005f));
        for (int k = 0; k < n; k++) {
            float s = ((float)k + 0.5f) * 2000.0f;
            func_0022E330(path, &point.q, &tangent.q, s);
            if (func_00167F60(hero, point.q, BcG(4000.0f))) continue;
            qword v = func_001C9428(0, actor, point.q);
            if (Xr(v) < 0.0f) continue;
            if (Xr(v) < __builtin_fabsf(Y(v))) continue;
            float d = LengthXY(Sub(MATRIX(actor)->position, point.q));
            if (best < d) continue;
            int side;
            if (s < param)
                side = (param - s) < func_0022DFD8(path) * 0.5f;
            else
                side = func_0022DFD8(path) * 0.5f < (s - param);
            best = d;
            result = e;
            M3 rotation;
            M3 *prot = &rotation;
            float heading = func_001205C8(tangent.q);
            func_0011C8C0(prot, heading, D_00317550);
            bestPoint = point;
            bestBasis = rotation;
            flag = side;
        }
    }
    *outPoint = bestPoint.q;
    *outBasis = bestBasis;
    *outFlag = flag;
    func_001D2798(&guard, 2);
    return result;
}
