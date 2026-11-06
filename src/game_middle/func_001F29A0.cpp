// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Attach the launched object (and its factory object) to the owner and prepare the launch state: the object comes
// from a factory object (class 8) or is passed directly (class 0x2F); class 0x6A objects are set up through func_001F9078,
// class 0x71 objects get a driver; the owner then caches the object's transform, launch velocity and aim point.
// Returns 0 (already attached), 1 (factory gave nothing), 2 (unsupported class) or 3.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct SO { char pad0[0xC]; VTE *vt; char pad10[0x60]; qword position; char pad80[0x188 - 0x80]; int driver; };
struct OWNER {
    char pad0[0x130];
    qword m[4];
    qword velocity;
    qword aim;
    float lifetime;
    SO *source;
    SO *factory;
    SO *first;
};
extern "C" {
extern qword D_00325020;
extern float D_00325030;
struct Clock { float time; float delta; };
extern Clock D_0036BB98;
extern char D_003174C0[];
extern char D_00475480[];
int func_0013B500(SO *, int);
SO *func_001FBE30(SO *, int);
void func_001FC060(SO *, SO *);
void func_001F9078(SO *, int);
int func_0017E5D8(void *, int, int, OWNER *);
SO *func_0023DDA0(OWNER *, int, int);
qword func_00212628(qword, qword, qword, float);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" int func_001F29A0(OWNER *self, SO *object, int index, int key)
{
    if (self->first)
        return 0;
    self->factory = 0;
    if (func_0013B500(object, 8)) {
        self->factory = object;
        self->first = func_001FBE30(object, 0);
        if (!self->first) {
            self->factory = 0;
            return 1;
        }
        func_001FC060(self->factory, self->first);
    } else {
        if (!func_0013B500(object, 0x2F))
            return 2;
        self->first = object;
    }
    if (func_0013B500(self->first, 0x6A)) {
        func_001F9078(self->first, index);
    } else if (func_0013B500(self->first, 0x71)) {
        SO *p = self->first;
        p->driver = func_0017E5D8(D_00475480, 3, 0x3A, self);
        VTE *e = &p->vt[80];
        ((void (*)(void *, int))e->fn)((char *)p + e->delta, 6);
    }
    self->source = func_0023DDA0(self, key, 0xD);
    float lifetime;
    if (func_0013B500(self->first, 0x71) && self->source) {
        float half = 0.5f;
        SO *p = self->first;
        VTE *e = &p->vt[36];
        qword *m = ((qword *(*)(void *))e->fn)((char *)p + e->delta);
        self->m[0] = m[0];
        self->m[1] = m[1];
        self->m[2] = m[2];
        qword row = m[3];
        self->m[3] = row;
        self->velocity = func_00212628(row, self->source->position, D_00325020, half);
        self->aim = AddScaled(self->velocity, D_00325020, VU_FLOAT(half));
        lifetime = D_0036BB98.time + half;
    } else {
        lifetime = D_00325030;
    }
    self->lifetime = lifetime;
    {
        SO *p = self->first;
        VTE *e = &p->vt[9];
        ((void (*)(void *))e->fn)((char *)p + e->delta);
    }
    if (self->source) {
        SO *p = self->first;
        VTE *e = &p->vt[10];
        ((void (*)(void *, OWNER *, SO *, int))e->fn)((char *)p + e->delta, self, self->source, 0);
        p = self->first;
        e = &p->vt[43];
        ((void (*)(void *, SO *, void *))e->fn)((char *)p + e->delta, self->source, D_003174C0);
    }
    return 3;
}
