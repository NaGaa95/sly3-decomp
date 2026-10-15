// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct G {
    char pad[0x4DFC];
    void *p45CC;
};
extern struct G D_00475480;
struct I {
    char pad[0x118];
    void *p128;
};
struct D {
    char pad[0x10];
    void *p10;
};
struct C {
    char pad[0xDC];
    struct D *pDC;
};
struct VTE {
    short delta;
    short pad;
    void (*target)(void *);
};
struct MATRIX4 {
    qword rows[4];
};
struct A {
    char pad[0xC];
    struct VTE *vt;
    char pad10[0xD8 - 0x10];
    struct C *pE8;
};
struct V2 {
    qword a;
    qword b;
};
struct S {
    char pad[0x10];
    struct A *p10;
    char pad2[0x2C];
    struct V2 v40;
    union {
        struct V2 v60;
        struct {
            int n60;
            int n64;
            char pad[8];
            qword v70;
        }
        s;
    }
    u;
    char pad3[0x98 - 0x80];
    int nB4;
    struct I *aB8[1];
    int nBC;
    int nC0;
};
static __inline__ struct MATRIX4 *Matrix(struct A *p) {
    return ((struct MATRIX4 *(*)(void *))p->vt[36].target)((char *)p + p->vt[36].delta);
}
qword func_001EE788(struct V2 *p, qword v);
void *func_001ED678(qword v, int n);
int func_001EEA90(void *a, struct A *b, qword v, int c, int d, struct I **pp);
void func_001ED190(void *a, qword v, qword *pv, int n);
void func_001D7B80(struct S *p) {
    p->nB4 = 0;
    p->u.v60 = p->v40;
    if (p->nBC == 0) {
        qword pos = Matrix(p->p10)->rows[3];
        qword v = func_001EE788(&p->v40, pos);
        struct C *c = p->p10->pE8;
        struct D *d = c ? c->pDC : 0;
        void *q = d ? d->p10 : 0;
        void *r;
        int fail;
        r = func_001ED678(v, 0);
        fail = 0;
        if (r == 0) {
            fail = 1;
        }
        else if (r != q) {
            struct G *g = &D_00475480;
            int n;
            if ((p->nB4 = func_001EEA90(g->p45CC, p->p10, v, 1, 1, p->aB8)) <= 0) {
                if (p->nC0 == 0) {
                    fail = 1;
                }
                else {
                    n = func_001EEA90(g->p45CC, p->p10, v, 0, 1, p->aB8);
                    p->nB4 = n;
                    if (n == 0) {
                        fail = 1;
                    }
                    else {
                        void *a;
                        if (p->aB8[0] == 0) {
                            a = q;
                            p->nB4 = 0;
                        }
                        else {
                            a = p->aB8[n - 1]->p128;
                        }
                        p->u.s.n60 = 0;
                        p->u.s.n64 = 0;
                        func_001ED190(a, v, &p->u.s.v70, 1);
                    }
                }
            }
        }
        if (fail) {
            p->u.s.n60 = 0;
            p->u.s.n64 = 0;
            p->u.s.v70 = pos;
        }
    }
}
