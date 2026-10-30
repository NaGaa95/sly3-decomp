// SLY3_CFLAGS: -Os -G0
// SLY3_ASFIX: engine-divfix1
struct Scope { unsigned char unused_storage[16]; };
void func_002BBEC8(void *, int);
void func_00148890(void *s, int i);
struct E { int a, b, c; };
struct N { char pad[0x1C]; float f; char pad2[0x2C - 0x20]; struct N *next; };
struct S { char pad[0x40]; struct N *first; char pad2[0x64 - 0x44]; float scale; char pad3[0x90 - 0x68];
           int n94; char *x94; char pad4[0xB0 - 0x98]; int stride; int n; char *base; int ne; struct E *e;
           char pad5[0xC8 - 0xC4]; struct S *ref; };
void func_00148588(struct S *s, int a, int b, int c, float *scale);
void func_00148938(struct S *s)
{
    struct Scope scope;
    int i, j, k;
    struct N *p;
    i = s->n;
    do
        i--;
    while (i >= 0 && !(*(float *)(s->base + i * s->stride) > 0.9999f));
    func_00148890(s, i);
    for (p = s->first; p; p = p->next)
        p->f /= s->scale;
    for (j = 0; j < s->ne; j++) {
        struct E *e = &s->e[j];
        func_00148588(s, e->a, e->b, e->c, &s->scale);
    }
    if (!s->ne)
        func_00148588(s, 0, 0, 0, &s->scale);
    for (p = s->first; p; p = p->next)
        p->f *= s->scale;
    if (s->ref) {
        float r = s->scale / s->ref->scale;
        for (k = 0; k < s->n94; k++)
            *(float *)(s->x94 + k * 20) = r * *(float *)(s->ref->x94 + k * 20);
    }
    func_002BBEC8(&scope, 2);
}
