// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00174490).
extern "C" {
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
struct R { char pad[0x29C]; char sub29C[0x324 - 0x29C]; int n324; char pad2[0x1160 - 0x328]; int n1160; };
struct Q { int pad[2]; int n8; };
struct M { int n0; int pad; void *p8; int nC; struct Q *p10; };
struct S { char pad[0x80]; int n80; struct O **a84; };
struct R *func_001FBE30(void *p, int n);
void func_00198D78(qword *pv, float a, float b, int c, int d);
int func_0011E8F0(int lo, int hi);
void *func_002387A8(void *p, int n);
void *memset(void *p, int c, unsigned int n);
void func_0013BD00(struct R *r, struct S *p);
}
struct F { int a; int rest[3]; F() { memset(this, 0, sizeof *this); } };
extern "C" {
void func_0019A2D0(void *o, struct F *f);
}
extern "C" struct R *func_00199D48(struct S *p, struct M *m, qword *pv, int a3, int t0) {
    struct R *r = 0;
    int k;
    switch (m->n0) {
    case 0:
        r = func_001FBE30(m->p8, 0);
        break;
    case 1:
    case 2:
      {
        int idx[8];
        int i, j, l;
        func_00198D78(pv, 100.0f, -350.0f, 0, 0);
        for (l = 0; l < p->n80; l++) idx[l] = l;
        for (j = 0; j < p->n80; j++) {
            int i = func_0011E8F0(0, p->n80 - 1);
            int t = idx[j];
            idx[j] = *(i + idx); *(i + idx) = t;
        }
        for (i = 0; i < p->n80; i++) {
            struct O *o = p->a84[idx[i]];
            { struct VTE *e = &o->vt[0x22]; ((void (*)(void *, qword))e->pfn)((char *)o + e->d, *pv); }
            { struct VTE *e = &o->vt[0x23]; ((void (*)(void *, int))e->pfn)((char *)o + e->d, a3); }
            r = func_001FBE30(o, 0);
            if (r) break;
        }
    k = m->n0;
        if (k == 1) {
            void *o;
            if (r) {
            m->p10->n8 = t0;
            r->n324 = m->nC;
            o = func_002387A8(r->sub29C, 0xC8);
            F f;
            f.a = -1;
            func_0019A2D0(o, &f);
            f.a = k;
            func_0019A2D0(o, &f);
            }
        }
      }
        break;
    }
    if (r) {
        r->n1160 = 1;
        func_0013BD00(r, p);
    }
    return r;
}
