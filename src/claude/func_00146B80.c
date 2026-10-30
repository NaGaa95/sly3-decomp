// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *, ...); };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x1E0 - 0x10]; qword x1E0; };
struct G { char pad[0x4E2C]; float r; };
extern struct G D_00475480;
void *func_0017E1B8(void *g, int a, int b, int c);
qword func_00146A80(void *s);
void func_0022EA88(void *o, qword pos, int a, qword *out, int b, int c, int d);
qword func_001205F0(qword v, float r);
void func_0011CBA0(M3 *r, qword v);
void func_0011CCF8(M3 *a, int b, M3 *c);
qword func_0011D3C0(void *m);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
void func_00146B80(struct S *s)
{
    qword p;
    U pos, dir, d;
    M3 m;
    void *o = func_0017E1B8(&D_00475480, 5, 0x78B, 0);
    p = func_00146A80(s);
    pos.q = p;
    if (o) {
        func_0022EA88(o, MATRIX(s)->rows[3], 0, &dir.q, 0, 0, 0);
    } else {
        d.q = Sub(p, MATRIX(s)->rows[3]);
        d.f[2] = 0.0f;
        d.q = func_001205F0(d.q, D_00475480.r - 1000.0f);
        dir.q = Sub(pos.q, d.q);
    }
    s->methods[34].call((unsigned char *)s + s->methods[34].delta, dir.q);
    {
        M3 t;
        func_0011CBA0(&t, Sub(pos.q, dir.q));
        m = t;
    }
    func_0011CCF8(&m, 0, &m);
    s->methods[35].call((unsigned char *)s + s->methods[35].delta, &m);
    s->x1E0 = func_0011D3C0(MATRIX(s));
}
