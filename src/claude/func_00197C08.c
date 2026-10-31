// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_001715F0).
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void (*method)(); };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct K8 { float a, b; };
struct A { char pad[0xC]; struct VTE *vt; char p0[0x29C - 0x10]; char x29C[0x308 - 0x29C]; struct K8 k308; struct K8 k310;
    char p1[0x340 - 0x318]; float g340; char p2[0x10F0 - 0x344]; int n10F0; };
struct CMD { int op; int n4; union { struct K8 k8; struct { int n8; int nC; } s; } u; union { int n10; float g10; } u10; int n14; int n18; };
struct P38 { int n0; int n4; void *p8; float gC; };
struct X60 { int n60; int n64; int n68; int n6C; };
struct P44 { int a, b; float g8; };
struct S { char pad[0xC]; struct VTE *vt; struct A *p10; char pad1[0x30 - 0x14];
    void *p30; void *n34; struct P38 *p38; float g3C; int n40; struct P44 *p44; char pad2[0x60 - 0x48];
    struct X60 x60; };
struct X { void *p0; void *p4; int pad[2]; qword q; };
struct M3 { qword r[3]; };
struct M4 { qword r[3]; qword pos; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern qword D_00317550;
void *func_00197B98(struct S *p, int oid);
void func_00198250(struct S *p, void *o, qword *pq, float *pg);
void func_00198D78(qword *pq, int a, int b, float f, float g);
void func_0011C8C0(struct M3 *pm, qword ax, float g);
void func_002BA818(qword *pdst, qword q);
struct OBJ *func_00238690(void *pv, int k);
void func_0024E878(struct A *a, float g);
void func_00231948(void *o);
void func_001983A8(struct S *p, int a, int b, int c);
void func_001DA6F0(void *o, void *p);
void func_001DA388(void *o, void *p);
void func_002B8750(struct X *x);
int func_0013B500(void *o, int n);
void func_001D7FD0(void *o, struct X *x);
void func_00136908(void *o, int a, int b, void *c, float f, float g);
void *func_001977A0(void *p, int id);
void func_002389C0(struct S *p);
void func_00238A38(struct S *p);
void func_00254BB8(struct X60 *x, struct A *a);
void func_00254C00(struct X60 *x, struct A *a);
void func_002261A0(void *o, int n);

struct O2 { char pad[0xC]; struct VTE *vt; char pad1[0x30 - 0x10]; void *p30; int n34; float g38; char pad2[0x50-0x3C]; void *n50; int pad3; int n58; };
struct O3 { char pad[0xC]; struct VTE *vt; char pad1[0x88 - 0x10]; void *n88; int pad2; float g90; int pad3[3]; int nA0; };
struct O4 { char pad[0xC]; struct VTE *vt; char pad1[0xC0 - 0x10]; void *pC0; int nC4; int nC8; int nCC; };
struct O5 { char pad[0xC]; struct VTE *vt; char pad1[0x38 - 0x10]; void *p38; int pad2; struct X60 *p40; };

#define VCALL8(po) ((void (*)(void *))(po)->vt[8].method)((char *)(po) + (po)->vt[8].delta)

void func_00197C08(struct S *p, struct CMD *c)
{
    int n;
    union { struct { union { qword q; } q; struct M4 mat; struct M3 m; } c3; struct X x; } u;
    switch (c->op) {
    case 0:
        p->n34 = func_00197B98(p, c->n4);
        break;
    case 1:
        p->p10->k308 = c->u.k8;
        break;
    case 2:
        p->p10->k310 = c->u.k8;
        break;
    case 3: {
        float g;
        struct A *a;
        struct M4 *pmat;
        func_00198250(p, func_00197B98(p, c->n4), &u.c3.q.q, &g);
        if (c->u.s.n8) func_00198D78(&u.c3.q.q, 0, 0, 100.0f, -350.0f);
        func_0011C8C0(&u.c3.m, D_00317550, g);
        pmat = &u.c3.mat;
        func_002BA818(&pmat->pos, u.c3.q.q);
        u.c3.mat.r[0] = u.c3.m.r[0];
        pmat->r[1] = u.c3.m.r[1];
        pmat->r[2] = u.c3.m.r[2];
        ((int *)&u.c3.mat.r[2])[3] = 0;
        ((int *)&u.c3.mat.r[1])[3] = 0;
        ((int *)&u.c3.mat.r[0])[3] = 0;
        ((float *)&pmat->pos)[3] = 1.0f;
        a = p->p10;
        ((void (*)(void *, int, struct M4 *))a->vt[0x2B].method)((char *)a + a->vt[0x2B].delta, 0, pmat);
        break;
    }
    case 4: {
        void *apv;
        apv = &c->n4;
        ((void (*)(void *, int, int, int, void **, int))p->vt[3].method)((char *)p + p->vt[3].delta, 4, 0, 1, &apv, 0);
        break;
    }
    case 5: {
        struct A *a = p->p10;
        float g;
        int f = 0;
        switch (a->n10F0) {
        case 2: {
            struct OBJ *o = func_00238690(a->x29C, 0xE2);
            VCALL8(o);
            f = 1;
            break;
        }
        case -1: {
            struct OBJ *o = func_00238690(a->x29C, 0xCA);
            VCALL8(o);
            f = 1;
            break;
        }
        }
        if (f) {
            void *o = func_00197B98(p, c->n4);
            if (o) {
                func_00198250(p, o, 0, &g);
                func_0024E878(p->p10, g);
            }
        }
        p->n40 = 1;
        break;
    }
    case 6: {
        void *o = func_00197B98(p, p->p38->n4);
        struct A *a;
        if (!o) break;
        a = p->p10;
        switch (a->n10F0) {
        case -1: {
            struct O2 *o2 = (struct O2 *)func_00238690(a->x29C, 0xE6);
            o2->p30 = o;
            o2->n34 = c->u.s.n8;
            o2->n58 = c->n14;
            if (!c->n14) func_00231948(o);
            if (p->p44) o2->g38 = p->p44->g8;
            if (c->u.s.nC != -1) o2->n50 = func_00197B98(p, c->u.s.nC);
            if (c->u10.n10 != -1) func_001983A8(p, 0xE, c->u10.n10, 8);
            VCALL8(o2);
            break;
        }
        case 0: {
            struct OBJ *o2 = func_00238690(a->x29C, 0xDF);
            func_001DA6F0(o2, p->p38->p8);
            VCALL8(o2);
            break;
        }
        case 1: {
            struct OBJ *o2 = func_00238690(a->x29C, 0xE0);
            func_001DA388(o2, p->p38->p8);
            VCALL8(o2);
            break;
        }
        }
        p->n40 = 1;
        break;
    }
    case 7: {
        struct P38 *qq;
        struct A *a;
        func_002B8750(&u.x);
        qq = p->p38;
        if (qq->n4 == -1) {
            u.x.q = *(qword *)qq->p8;
        } else {
            void *o = func_00197B98(p, qq->n4);
            if (o) {
                if (func_0013B500(o, 9)) u.x.p0 = o;
                else u.x.p4 = o;
            }
        }
        a = p->p10;
        if (a->n10F0 == -1) {
            struct O3 *o3 = (struct O3 *)func_00238690(a->x29C, 0xE1);
            func_001D7FD0(o3, &u.x);
            if (c->u.s.nC != -1) o3->n88 = func_00197B98(p, c->u.s.nC);
            if (c->n14 != -1) func_001983A8(p, 0xE, c->n14, 8);
            o3->g90 = c->u10.g10;
            o3->nA0 = c->n18;
            VCALL8(o3);
        }
        p->n40 = 1;
        break;
    }
    case 8: {
        int t;
        func_00136908(func_00197B98(p, c->n4), 0, 0, &t, 0.0f, 1.0f);
        break;
    }
    case 9:
        break;
    case 10: {
        void *o = func_001977A0(p->p30, c->n4);
        if (o) p->p38 = (struct P38 *)o;
        break;
    }
    case 11:
        func_002389C0(p);
        break;
    case 12:
        func_00238A38(p);
        break;
    case 13: {
        void *o = func_00197B98(p, p->p38->n4);
        struct O4 *o4 = (struct O4 *)func_00238690(p->p10->x29C, 0xCB);
        o4->pC0 = o;
        o4->nCC = 1;
        o4->nC4 = c->u.s.n8;
        o4->nC8 = c->u.s.nC;
        VCALL8(o4);
        p->n40 = 1;
        break;
    }
    case 14:
        func_00254BB8(&p->x60, p->p10);
        p->x60.n64 = c->n4;
        p->x60.n6C = c->u.s.n8;
        func_00254C00(&p->x60, p->p10);
        n = p->p10->n10F0;
        if (n < 3) if (n >= -1) {
            struct O5 *o5 = (struct O5 *)func_00238690(p->p10->x29C, 0xC9);
            o5->p40 = &p->x60;
            VCALL8(o5);
            p->n40 = 1;
        }
        break;
    case 15:
        func_002261A0(func_00197B98(p, c->n4), c->u.s.n8);
        break;
    case 16:
        func_0024E878(p->p10, p->p10->g340);
        break;
    case 17: {
        void *o = func_00197B98(p, p->p38->n4);
        struct O5 *o6 = (struct O5 *)func_00238690(p->p10->x29C, 0xED);
        o6->p38 = o;
        VCALL8(o6);
        p->n40 = 1;
        break;
    }
    case 18: {
        void *o = func_00197B98(p, p->p38->n4);
        struct O5 *o6 = (struct O5 *)func_00238690(p->p10->x29C, 0xEC);
        o6->p38 = o;
        VCALL8(o6);
        p->n40 = 1;
        break;
    }
    }
    p->g3C = g_clock.t;
}
