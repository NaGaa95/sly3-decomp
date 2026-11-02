// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad0[0x120]; VTE matrix; char pad128[0x140 - 0x128]; VTE setVelocity; VTE setSpin; };
struct CLOCK { float t, dt; };
struct Body {
    char pad0[0xC]; VT *pvt;
    char pad10[0x130 - 0x10]; int handle;
    char pad134[0x380 - 0x134]; int mode;
    float modeTime;
    void *path;
    float pathTime;
    char pad390[0x3FC - 0x390]; int flag;
    char pad400[0xC70 - 0x400]; M3 basis;
    qword target;
    float duration, radius;
    char padCB8[8];
    qword axis;
};
extern CLOCK D_0036BB98;
extern char D_00475480[];
extern qword D_00317560, D_00325880;
extern "C" {
void func_0023EBF8(Body *, int);
void func_0023EC98(Body *, int);
void func_0023FC90(Body *, int);
void func_001A9420(void *, int, int);
void func_001A94F0(void *, int);
void func_001A93C8(void *, int, int);
void func_001A94A8(void *, int);
void func_0022EA88(void *path, qword anchor, int kind, void *position, void *direction, float *progress, float *length);
M3 func_0011CFC0(M3 *pa, M3 *pb);
void func_0011D0B8(M3 *pmat, float *prad, qword *pvec);
void func_002075E8(Body *self, int mode);
}
static inline M4 *Matrix(Body *b)
{
    VTE *e = &b->pvt->matrix;
    return ((M4 *(*)(void *))e->pfn)((char *)b + e->d);
}
static inline void SetVelocity(Body *b, qword v)
{
    VTE *e = &b->pvt->setVelocity;
    ((void (*)(void *, qword))e->pfn)((char *)b + e->d, v);
}
static inline void SetSpin(Body *b, qword v)
{
    VTE *e = &b->pvt->setSpin;
    ((void (*)(void *, qword))e->pfn)((char *)b + e->d, v);
}
struct VUF {
    qword q;
    VUF(float g) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g)); }
};
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulAdd(qword a, qword s, qword b, qword t)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(s), "j"(a), "j"(b), "j"(t));
    return r;
}
extern "C" void func_002075E8(Body *self, int mode)
{
    if (mode == self->mode)
        return;
    if (self->mode == 4) {
        func_0023EBF8(self, 0);
        func_0023EC98(self, 0);
        func_0023FC90(self, 0);
        SetVelocity(self, D_00317560);
        SetSpin(self, D_00317560);
        self->flag = 1;
        func_001A9420(D_00475480, self->handle, 2);
        func_001A94F0(D_00475480, self->handle);
    }
    self->mode = mode;
    self->modeTime = D_0036BB98.t;
    if (mode < 2)
        return;
    switch (mode) {
    case 2:
    case 3:
        func_0022EA88(self->path, Matrix(self)->r[3], 0, 0, 0, 0, &self->pathTime);
        break;
    case 4: {
        U result;
        M3 mat;
        qword inv = VUF(1.0f / self->duration).q;
        qword target = self->target;
        M4 *m = Matrix(self);
        result.q = MulAdd(Sub(target, m->r[3]), inv, D_00325880, VUF(self->duration * -0.5f).q);
        SetVelocity(self, result.q);
        SetSpin(self, D_00317560);
        mat = func_0011CFC0(&self->basis, (M3 *)Matrix(self));
        func_0011D0B8(&mat, &self->radius, &self->axis);
        func_0023EBF8(self, 1);
        func_0023EC98(self, 1);
        func_0023FC90(self, 1);
        func_001A93C8(D_00475480, self->handle, 2);
        func_001A94A8(D_00475480, self->handle);
        break;
    }
    }
}
