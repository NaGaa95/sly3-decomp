// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct RGBA { unsigned char r, g, b, a; };
struct X { float a[4]; struct RGBA c; int n14; int n18; };
struct S {
    char pad[0x6C]; float f6C, f70, f74, f78, f7C, f80, f84, f88;
    char pad8C[0x198 - 0x8C]; int n198; int n19C; int n1A0;
};
struct T { float f0, f4, f8, fC, f10, f14, f18, f1C; };
struct U { qword q[4]; };
struct V { float f0, f4, f8, fC; qword a, b; };
extern qword D_003175A0, D_003175B0;
extern char D_00327F28[];
void *memset(void *, int, unsigned int);
void func_00264B70(struct S *, struct RGBA *);
void func_00265000(struct S *);
void func_00265308(struct S *, struct U *, struct T *);
void func_00265660(struct S *, struct U *, struct V *);
void func_002618C8(int, void *, const char *, const char *, float);
static inline void Clear(struct T *t) { memset(t, 0, sizeof(*t)); }
void func_00265480(struct S *p, struct X *x, int n)
{
    if (x) {
        struct RGBA c;
        struct T t;
        struct U u;
        struct V v;
        p->f6C = x->a[0];
        p->f70 = x->a[1];
        p->f74 = x->a[2];
        p->f78 = x->a[3];
        p->n19C = x->n14;
        p->n198 = x->n18;
        p->n1A0 = n;
        c = x->c;
        func_00264B70(p, &c);
        func_00265000(p);
        Clear(&t);
        t.fC = p->f80 * p->f88;
        t.f0 = p->f7C * p->f88;
        t.f10 = p->f6C;
        t.f14 = p->f70 + p->f84 * p->f80;
        func_00265308(p, &u, &t);
        v.a = D_003175A0;
        v.f8 = 16.0f;
        v.b = D_003175B0;
        func_00265660(p, &u, &v);
        func_002618C8(0, 0, D_00327F28, "rich text", p->n1A0);
    }
}
