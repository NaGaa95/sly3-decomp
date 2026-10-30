// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct Method { short delta, reserved; void *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct E { struct Object *o; int on; };
struct S { unsigned char pad00[0xC]; struct Method *methods; char pad[0x138 - 0x10]; int ne; struct E e[8];
           int nk; int k[1]; };
extern char D_0036E740[];
extern char D_00475480[];
struct Object *func_001F4B30(void *p);
int func_0017E208(void *g, int a, int b, int c, int max, struct Object **out);
void func_0011D768(M4 *m, M4 *src);
int func_001C8610(struct Object *o);
int func_0027F298(struct S *s, qword p);
#define MATRIX(o) ((M4 *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))
static inline qword Xform(M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddaz.xyz $ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w"
            : "=j"(r) : "j"(m->r[0]), "j"(v), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
int func_0015D2F0(struct S *s, int max, struct Object **out)
{
    struct Object *list[64];
    M4 m;
    int n = 0;
    int i;
    int cnt;
    int l;
    if (!s->ne && !s->nk) {
        for (i = 0; i < 2; i++) {
            struct Object *o = func_001F4B30(D_0036E740 + i * 0x11C0);
            if (o)
                list[n++] = o;
        }
    } else {
        int j, k;
        for (j = 0; j < s->ne; j++) {
            struct E *e = &s->e[j];
            if (e->on)
                list[n++] = e->o;
        }
        for (k = 0; k < s->nk; k++)
            n += func_0017E208(D_00475480, 0x505, s->k[k], 0, 64 - n, &list[n]);
    }
    if (!n)
        return 0;
    {
        cnt = 0;
        func_0011D768(&m, MATRIX(s));
        for (l = 0; l < n; l++) {
            struct Object *o = list[l];
            qword q;
            if (!func_001C8610(o))
                continue;
            q = Xform(&m, MATRIX(o)->r[3]);
            if (!func_0027F298(s, q))
                continue;
            out[cnt++] = o;
            if (cnt >= max)
                break;
        }
        return cnt;
    }
}
