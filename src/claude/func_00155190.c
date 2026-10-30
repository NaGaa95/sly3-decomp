// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
void *func_0023DDA0(void *s, void *a, int k);
void func_0011C6F8(M3 *m, void *p);
qword func_0011D3C0(M3 *m);
void *func_00130078(void *s, void *o, int a, int b, int c, qword q);
void func_0012F410(void *p);
struct O { char pad[0x40]; M3 m; };
struct S { char pad[0x50]; char *x50; char pad2[0x11CC - 0x54]; void *x11CC; char pad3[0x1220 - 0x11D0]; M3 m; };
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
void func_00155190(struct S *s, void *a)
{
    struct O *o = func_0023DDA0(s, a, 6);
    M3 t;
    M3 mat;
    if (!o)
        return;
    func_0011C6F8(&mat, s->x50 + 0x40);
    MulMat(&t, &mat, &o->m);
    s->m = t;
    s->x11CC = func_00130078(s, o, 3, 8, 2, func_0011D3C0(&s->m));
    func_0012F410(s->x11CC);
}
