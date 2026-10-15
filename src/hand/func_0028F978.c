// Evaluate linked animation records with state threshold six, deduplicate affected objects, update transforms and generation counters, and dispatch the original virtual notifications; the complete original table also excludes Sly 3 state six.
// Reference algorithm: src/hand/func_00230CF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
typedef struct VT { short d; short pad; void (*pfn)(); } VT;
typedef struct LO { char pad[0xC]; VT *vt; } LO;
typedef struct P {
    qword m[4];
    char pad40[0x80 - 0x40];
    float x80;
    float x84;
    float *x88;
    float *x8C;
    char pad90[0x98 - 0x90];
    short x98;
    short x9A;
    char pad9C[0xA4 - 0x9C];
    int xA4;
    char padA8[0xB0 - 0xA8];
    qword xB0;
    qword xC0[4];
} P;
typedef struct C { char pad0[4]; LO *x4; P *x8; char padC[0x28 - 0xC]; struct C *x28; } C;
typedef struct OBJ { VT *vt; } OBJ;
typedef struct E { OBJ *x0; int x4; char pad8[8]; struct E *x10; } E;
typedef struct A { char pad0[0x1C]; float x1C; char pad20[0x34 - 0x20]; C *x34; E *x38; char pad3C[4]; float x40; } A;
typedef struct G { char pad[0x44F4]; int x3D58; } G;
extern G D_00475480;
extern qword D_00317560;
int func_00138AC8(A *);
int func_0012F2D0(C *);
void func_0028C8F0(LO *, P *, int);
qword func_0028B388(P *, P *);
qword func_0011D3C0(qword *);
M4 func_0028B230(P *, qword);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, int, int);

void func_0028F978(A *a, int flag)
{
    LO *list[16];
    int n;
    C *c;
    int i;
    struct { float f[4]; } __attribute__((aligned(16))) out;

    if (func_00138AC8(a))
        return;
    n = 0;
    for (c = a->x34; c; c = c->x28) {
        P *p;
        LO *q;
        qword v;
        if (!func_0012F2D0(c))
            continue;
        p = c->x8;
        q = c->x4;
        func_0028C8F0(q, p, 6);
        switch (p->x98) {
        case 0: case 6: case 14:
            continue;
        case 8: case 9: case 10: case 12:
            if (!flag)
                continue;
            break;
        }
        for (i = 0; i < n; i++)
            if (q == list[i])
                break;
        if (i >= n && (unsigned)n < 16)
            list[n++] = q;
        switch (p->x9A) {
        case 0:
            v = func_0028B388(p, p);
            break;
        case 1: {
            func_00118558(p->x84 - p->x80, *p->x88 - p->x80, *p->x8C, p->xC0[0], p->xC0[1], p->xC0[2], p->xC0[3], (qword *)&out, 0, 0);
            v = *(qword *)&out;
            break;
        }
        case 2: case 3: case 4:
            v = p->xC0[0];
            break;
        case 5:
            v = func_0011D3C0(p->xC0);
            break;
        default:
            v = D_00317560;
            break;
        }
        {
            M4 t = func_0028B230(p, v);
            *(M4 *)p->m = t;
        }
        p->xB0 = D_00317560;
        p->xA4 = ++D_00475480.x3D58;
    }
    for (i = 0; i < n; i++)
        list[i]->vt[20].pfn((char *)list[i] + list[i]->vt[20].d);
    {
        E *e;
        for (e = a->x38; e; e = e->x10)
            ((void (*)(void *, int, int, float, float))e->x0->vt[2].pfn)((char *)e->x0 + e->x0->vt[2].d, e->x4, 0, a->x1C, a->x40);
    }
}
