// Reference: Sly 2 src/hand/func_00259498.c; target Sly 3 0x002BD8C8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct AREQ { int cb; int cbAlign; } AREQ;
int func_001D2538(AREQ *preq);
static inline int New(unsigned int cb) { AREQ req; req.cb = cb; req.cbAlign = 0x10; return func_001D2538(&req); }
typedef struct { char pad[0x10]; int x10; char pad2[0x1C]; int x30; } T;
typedef struct { char pad[0xD4]; T *xD4; } S;
T *func_002BD548(S *, int);
void func_002BD8C8(S *p, int k)
{
    T *t;
    if (p->xD4->x10 == k) return;
    if (p->xD4->x10 != 0) return;
    t = func_002BD548(p, 1);
    t->x10 = k;
    switch (k) {
    case 1: t->x30 = New(0x20); break;
    case 2: t->x30 = -1; break;
    case 3: t->x30 = New(0x30); break;
    }
}
