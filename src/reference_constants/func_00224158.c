// Reference algorithm: src/hand/func_001DEDB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct { char pad[0x18]; int x18; } Q;
typedef struct { int pad; int x4; } R;
typedef struct { void *o; Q *q; void *r; int xC; } ENT;
typedef struct { char pad[0x180]; ENT a[2]; } OBJ;
extern struct G D_00475480;
void func_0017E208(struct G *, int, int, void *, int, Q **);
void *func_0023FAE8(void *, int);
void *func_00137428(Q *, void *, int, float, float);
R *func_00136EE0(Q *, void *, int, int);
void func_00224158(OBJ *p)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        ENT *e = &p->a[i];
        void *o = e->o;
        Q *q;
        R *r;
        if (o == 0)
            continue;
        func_0017E208(&D_00475480, 2, 0x82, o, 1, &e->q);
        q = e->q;
        if (q == 0)
            continue;
        e->r = func_0023FAE8(o, q->x18);
        if (e->r == 0) {
            e->r = func_00137428(q, o, 8, 0.0f, 1.0f);
            if (e->r == 0)
                continue;
        }
        r = func_00136EE0(q, o, 0xC, 1);
        if (r)
            e->xC = r->x4;
    }
}
