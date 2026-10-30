// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct Method { short delta, reserved; qword (*call)(void *); };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x14C - 0x10]; int mode; int busy;
           char pad2[0x160 - 0x154]; qword x160; M3 m; qword x1A0; qword x1B0; int x1C0; };
extern qword D_00317550;
void func_0011CBF0(M3 *m, qword a, qword b);
void func_0011CDC8(M3 *m, qword a, qword b);
#define MATRIX(o) ((M3 *)((void *(*)(void *))(o)->methods[36].call)((unsigned char *)(o) + (o)->methods[36].delta))
#define VCALL(o, n) ((o)->methods[n].call((unsigned char *)(o) + (o)->methods[n].delta))
static inline qword MulRow(M3 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
static inline void MulMat(M3 *pr, M3 *a, M3 *b)
{
    M3 r;
    r.r[0] = pr->r[0] = MulRow(a, b->r[0]);
    r.r[1] = pr->r[1] = MulRow(a, b->r[1]);
    pr->r[2] = r.r[2] = MulRow(a, b->r[2]);
}
void func_0014C9B8(struct S *s, qword a, qword b, int c)
{
    M3 m;
    M3 t;
    qword q;
    /* register pin: keeps b in $s2 as in the original allocation */
    register qword bb asm("$18") = b;
    if (s->busy)
        return;
    s->x160 = a;
    s->busy = 1;
    s->x1A0 = VCALL(s, 38);
    s->x1B0 = VCALL(s, 39);
    s->x1C0 = c;
    switch (s->mode) {
    case 0:
        q = MATRIX(s)->r[2];
        goto mul;
    case 1:
        func_0011CBF0(&m, s->x1A0, D_00317550);
        s->m = m;
        break;
    case 2:
        q = MATRIX(s)->r[0];
    mul:
        func_0011CDC8(&m, q, bb);
        MulMat(&t, &m, MATRIX(s));
        s->m = t;
        break;
    case 3:
        s->m = *MATRIX(s);
        break;
    }
}
