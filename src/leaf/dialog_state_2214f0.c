// Switch the dialog to a new state (-1 closed, 0, 1, 2): stamp the change time, set the mode and the three text ids on the sub-panel, refresh it and notify the owner (Sly 2 func_001DD300).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct { short d; short pad; void *pfn; } VTE;
typedef struct Sub {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x48 - 0x10];
    int count;
    char pad4C[0x60 - 0x4C];
    int text60;
    int text64;
    int text68;
} Sub;
typedef struct { int x0, x4, x8; } Entry;
typedef struct Obj {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x34 - 0x10];
    Sub *sub;
    char pad38[0x50 - 0x38];
    int state;
    float stateTime;
    int count;
    Entry entries[1];
    char pad68[0x11C - 0x68];
    int mode;
    int target;
    int flag;
    int index;
    int a12C, a130, a134;
} Obj;
typedef struct { char pad[0x50]; int value; } Probe;
extern struct { char pad[0x40]; float t40; } D_0036BB98;
extern char D_00475480[];
extern int D_004794C4;
extern char D_004BC230[];
extern Probe *D_004BC244;
void func_001A93C8(void *, int, int);
void func_001A9420(void *, int, int);
void func_00261070(Sub *, int);
void func_00261050(Sub *, int);
int func_002852B0(void *);
int func_002835D0(Probe *);
void func_00262450(Sub *, int);
void func_00221108(Obj *);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
void func_002214F0(Obj *p, int s)
{
    int old;
    if (!p->sub)
        s = -1;
    if (s == p->state)
        return;
    if (p->state == -1)
        func_001A93C8(D_00475480, -1, 0);
    old = p->state;
    p->state = s;
    p->stateTime = D_0036BB98.t40;
    switch (s) {
    case -1:
        func_001A9420(D_00475480, -1, 0);
        VCALL(p, 11);
        if (p->sub->count > 0)
            func_00261050(p->sub, 1);
        p->a12C = s;
        p->a130 = s;
        p->a134 = s;
        break;
    case 0:
        p->mode = 0xA;
        p->sub->text60 = 0x570;
        p->sub->text68 = 0x56F;
        if (old == 1)
            p->sub->text64 = 0x575;
        else
            p->sub->text64 = 0x56E;
        if (p->sub->count) {
            func_00261070(p->sub, 1);
            func_00261050(p->sub, 2);
            VCALL(p->sub, 18);
        }
        break;
    case 1: {
        int i = p->index;
        if (i >= 0 && i < p->count)
            p->target = p->entries[i].x0;
        else
            p->target = D_004794C4;
        p->flag = (old == 0);
        p->mode = 4;
        p->sub->text60 = 0x573;
        p->sub->text68 = 0x572;
        if (old == 0)
            p->sub->text64 = 0x574;
        else
            p->sub->text64 = 0x571;
        if (p->sub->count) {
            func_00261070(p->sub, 1);
            func_00261050(p->sub, 2);
            VCALL(p->sub, 18);
            if (!func_002852B0(D_004BC230))
                func_00262450(p->sub, 0x576);
        }
        break;
    }
    case 2: {
        p->target = 0;
        p->flag = 0;
        p->mode = 0;
        p->sub->text60 = 0x63A;
        p->sub->text68 = 0x63B;
        p->sub->text64 = 0x639;
        if (p->sub->count) {
            int probe;
            func_00261070(p->sub, 1);
            func_00261050(p->sub, 2);
            VCALL(p->sub, 18);
            probe = D_004BC244 ? D_004BC244->value : -1;
            if (probe == 0)
                func_00262450(p->sub, func_002835D0(D_004BC244) ? 0x5D5 : 0x5D6);
        }
        break;
    }
    }
    func_00221108(p);
    ((void (*)(void *, int))p->vt[14].pfn)((char *)p + p->vt[14].d, -1);
}
