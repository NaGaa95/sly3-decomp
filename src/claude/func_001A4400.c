// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001A4400 / func_001A4800 share the unit .rodata (PMF constant, both jump tables, FLT_MAX literal), so they live in one file.
// Adapted from the Sly 2 decomp (func_00176098 / func_00176458).
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct VTE { short d; short pad; void (*pfn)(void *); };
struct X { qword a; qword v; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x20]; int n30; int pad3; int n38; int n3C; char pad40[0x5C - 0x40]; int n5C; char pad60[0x88 - 0x60]; int n88; int n8C; char pad90[0xA4 - 0x90]; int nA4; };
struct LO { char pad[0xC]; struct VTE *vt; };
struct A { char pad[0x29C]; char a29C[0x3D8 - 0x29C]; void *p3D8; char pad3DC[0x1080 - 0x3DC]; float f1080; };
struct P { char pad[0x50]; float f50; float f54; };
struct V { char pad[0x14]; int n14; };
struct SUB { char pad[0x50]; int n50; char pad54[8]; int n5C; };
struct OWNER { char pad[0x10]; void *region; };
struct TUNE { char pad[0xDC]; struct OWNER *owner; };
struct ACTOR { char pad[0xC]; struct VTE *vt; char pad10[0xD8 - 0x10]; struct TUNE *tuning; char padDC[0x344 - 0xDC]; float close, far; char pad34C[0x10AC - 0x34C]; int emit; float time; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct SUB *sub; char a1C[0x14]; struct LO *n30; int n34; float f38; struct P *p3C; int pad40; void *n44; char pad5[8]; qword v50; };
void func_00238AE8(void *p);
void func_002389A0(struct S *p);
int func_00238AA8(struct S *p);
int func_00254B80(void *p);
int func_001A4390(struct S *p);
int func_001A4318(struct S *p);
int func_001A3FE0(struct S *p);
float func_002575C0(void *p);
int func_00238AD0(struct S *p);
struct PMF { short delta; short index; void (*pfn)(void); };
void func_0015DC68(void *p, void *actor, struct PMF pmf, int n);
void func_00256CF8(void *actor, void *target);
void func_00255AE0(void);
extern float D_0047A3CC;
extern char D_00475480[];
void func_001A4800(struct S *p, int n, struct V *pv);
float func_0011E940(float a, float b);
struct O *func_00238690(void *p, int n);
void func_002566F0(void *p, int n);
void func_002B8750(struct X *x);
void func_001D7FD0(void *p, struct X *x);
int func_001ED678(qword v, int n);
void func_002BC760(void *p, void *pv);
void func_00238AB8(struct S *p);
static inline qword PosOf(struct LO *p)
{
    struct VTE *e = &p->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)p + e->d)[3];
}
/* .rodata of the original unit at 0x003221F0: a pointer-to-member constant (non-virtual func_00255AE0). */
static const struct PMF D_003221F0 = { 0, -1, func_00255AE0 };
static inline void *ActorRegion(struct ACTOR *actor)
{
    struct OWNER *owner = actor->tuning ? actor->tuning->owner : 0;
    return owner ? owner->region : 0;
}
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %2, %1" : "=j"(r) : "j"(b), "j"(a)); return r; }
static inline float GLengthXY(qword v)
{
    qword qw;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GLength(qword v)
{
    qword qw, one;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
void func_001A4400(struct S *p)
{
    struct X frame;
    int old;
    func_002389A0(p);
    do {
        old = p->n34;
        switch (old) {
        case 0:
        case 3: {
            float distance;
            void *region;
            qword point;
            if (func_00238AA8(p))
                break;
            if (func_00254B80(p->p10)) { func_001A4800(p, 5, 0); break; }
            if (func_001A4390(p)) { func_001A4800(p, 4, 0); break; }
            if (func_001A4318(p)) { func_001A4800(p, 1, 0); break; }
            if (func_001A3FE0(p)) { func_001A4800(p, 2, 0); break; }
            point = PosOf(p->n30);
            distance = GLengthXY(QwSub(point, PosOf((struct LO *)p->p10)));
            distance /= func_002575C0(p->p10);
            region = (void *)func_001ED678(point, 1);
            if (p->n34 != 0) {
                if (p->n34 != 3)
                    break;
                if (distance < ((struct ACTOR *)p->p10)->close && region == ActorRegion((struct ACTOR *)p->p10)) { func_001A4800(p, 0, 0); break; }
                if (p->n44 != region || 500.0f < GLength(QwSub(point, p->v50))) {
                    p->n44 = region;
                    p->v50 = point;
                    func_002B8750(&frame);
                    frame.v = point;
                    func_001D7FD0(p->sub, &frame);
                }
            } else {
                if (((struct ACTOR *)p->p10)->far < distance || region != ActorRegion((struct ACTOR *)p->p10))
                    func_001A4800(p, 3, 0);
            }
            break;
        }
        case 1:
            if (func_00254B80(p->p10)) { func_001A4800(p, 5, 0); break; }
            if (!func_00238AA8(p) && func_00238AD0(p))
                func_001A4800(p, 0, 0);
            break;
        case 2:
            if (func_00254B80(p->p10)) { func_001A4800(p, 5, 0); break; }
            if (!func_00238AA8(p) && func_00238AD0(p))
                func_001A4800(p, 0, 0);
            break;
        case 4:
            if (func_00238AD0(p))
                func_001A4800(p, -1, 0);
            break;
        case 8:
            if (func_00238AD0(p)) {
                if (p->sub->n50 == -1)
                    func_0015DC68(D_00475480, p->p10, D_003221F0, p->sub->n5C);
                func_001A4800(p, 3, 0);
            }
            break;
        case 6:
        case 7:
        case 9:
            if (func_00238AD0(p))
                func_001A4800(p, 3, 0);
            break;
        case 5:
            if (!func_00238AA8(p) && !func_00254B80(p->p10))
                func_001A4800(p, 3, 0);
            break;
        }
    } while (old != p->n34);
    {
        struct ACTOR *actor = (struct ACTOR *)p->p10;
        if (actor->emit && old < 4 && old >= 0 && actor->time <= g_clock.t && D_0047A3CC <= g_clock.t)
            func_00256CF8(actor, p->n30);
    }
}

void func_001A4800(struct S *p, int n, struct V *pv)
{
    if (n == p->n34 && n != 6 && n != 7 && n != 8 && n != 9)
        return;
    func_00238AE8(&p->sub);
    if (p->n34 == 1) {
        float t = g_clock.t;
        t += func_0011E940(p->p3C->f50, p->p3C->f54);
        p->p10->f1080 = t;
        p->p3C = 0;
    }
    p->n34 = n;
    p->f38 = g_clock.t;
    switch (n) {
    case 0:
        { struct O *o = func_00238690(p->p10->a29C, 0xDC); struct VTE *e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 1:
        {
            struct O *o = func_00238690(p->p10->a29C, 0xD1);
            struct VTE *e;
            o->n30 = (int)p->n30;
            o->n3C = (int)p->p3C;
            p->p10->f1080 = 3.40282347e+38f;
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        func_002566F0(p->p10->p3D8, 3);
        break;
    case 2:
        { struct O *o = func_00238690(p->p10->a29C, 0xD6); struct VTE *e; o->n38 = (int)p->n30; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        func_002566F0(p->p10->p3D8, 4);
        break;
    case 3:
        {
            struct O *o = func_00238690(p->p10->a29C, 0xE1);
            qword v1, v2;
            struct X x;
            struct VTE *e;
            o->nA4 = 1;
            o->n38 = 0x30;
            v1 = PosOf(p->n30);
            v2 = PosOf(p->n30);
            func_002B8750(&x);
            x.v = v2;
            func_001D7FD0(o, &x);
            o->n88 = (int)p->n30;
            o->n8C = 1;
            e = &o->vt[8]; e->pfn((char *)o + e->d);
            p->v50 = v1;
            p->n44 = (void *)func_001ED678(v1, 1);
        }
        break;
    case 4:
        { struct O *o = func_00238690(p->p10->a29C, 0xF2); struct VTE *e; o->n30 = (int)p->n30; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 5:
        { struct O *o = func_00238690(p->p10->a29C, 0xCA); struct VTE *e; o->n3C = 1; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 6:
        { struct O *o = func_00238690(p->p10->a29C, 0xCE); struct VTE *e; func_002BC760(&o->n30, pv); e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 7:
        { struct O *o = func_00238690(p->p10->a29C, 0xCF); struct VTE *e; func_002BC760(&o->n30, pv); e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 8:
        { struct O *o = func_00238690(p->p10->a29C, 0xDA); struct VTE *e; o->n5C = pv->n14; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case 9:
        { struct O *o = func_00238690(p->p10->a29C, 0xEA); struct VTE *e; o->n38 = (int)pv; e = &o->vt[8]; e->pfn((char *)o + e->d); }
        break;
    case -1:
        func_00238AB8(p);
        break;
    }
}
