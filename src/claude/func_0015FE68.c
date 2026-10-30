// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317560;
struct VEnt { short delta, pad; int (*fn)(); };
struct VT { struct VEnt e[1]; };
struct VObj { char pad[0xC]; struct VEnt *vt; };
struct O { char pad[0x2C]; struct VEnt *vt; };
struct G { char pad[0x18B0]; int state; };
struct P { char pad[0x10]; struct G *g; char pad2[0x30 - 0x14]; int v30; int v34; int v38; };
extern struct VObj *D_00370AC0;
struct O *func_0015F908(struct P *p);
void func_00160960(struct P *p, int a, int b);
void func_001614E8(struct P *p, int a);
void func_00161C60(struct G *g, int a);
void func_00162148(void *p);
int func_001F4430(struct G *g);
void func_001F4438(struct G *g, int n);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, Qword e, Qword f, int g);

void func_0015FE68(struct P *p)
{
    struct G *g = p->g;
    int s = g->state;
    struct O *o;
    int ok;
    int cost;

    if (s == -1)
        return;
    if (func_001F4430(g) <= 0)
        return;
    if (s == 0x33)
        func_00162148((char *)p->g + 0x1884);
    o = func_0015F908(p);
    if (!((int (*)(void *, int, float))o->vt[1].fn)((char *)o + o->vt[1].delta, 4, 0.0f))
        return;
    ok = 0;
    switch (s) {
    case 0x32:
        switch (p->v30) {
        case 0: case 1: case 2: case 3: case 4:
        case 11: case 15:
            ok = 1;
        }
        break;
    case 0x33:
        if (p->v38 == -1) {
            switch (p->v30) {
            case 0: case 1: case 2: case 3: case 4: case 5:
            case 6: case 7: case 8: case 9: case 10: case 11:
            case 19:
                ok = 1;
            }
        }
        break;
    case 0x34:
    case 0x35:
        if (p->v30 < 5)
            ok = p->v30 >= ok; /* ok is 0 here; comparing against it (not a literal 0) gives slti+xori */
        break;
    }
    if (!ok)
        return;
    cost = 0;
    switch (s) {
    case 0x32:
        cost = 0x22;
        func_00160960(p, 8, 0);
        break;
    case 0x33:
        cost = 0x22;
        func_001614E8(p, 4);
        break;
    case 0x34:
        cost = 0x64;
        func_00160960(p, 0x11, 0);
        break;
    case 0x35:
        cost = 0x64;
        if (D_00370AC0) {
            if (D_00370AC0->vt[81].fn((char *)D_00370AC0 + D_00370AC0->vt[81].delta))
                return;
            func_00240CB0(p->g, 0, D_00370AC0, 0x800000, 0, 0, D_00317560, D_00317560, 0);
        }
        break;
    }
    ((void (*)(void *, int))o->vt[2].fn)((char *)o + o->vt[2].delta, 4);
    func_001F4438(g, func_001F4430(g) - cost);
    if (func_001F4430(g) <= 0)
        func_00161C60(g, -1);
}
