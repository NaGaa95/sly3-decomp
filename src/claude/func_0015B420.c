// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct O {
    unsigned char pad00[0xC]; struct Method *methods; int pad10; void *item; unsigned char pad18[0x28 - 0x18];
    long low : 48; long kind : 4; long high : 12;
    int pad30; float range;
};
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
extern int D_00479390;
int func_0015AF58(void *self, int *pmask, struct V4 *out);
float func_0015B068(qword pos, int n, struct V4 *v);
int func_0011B0C0(void *, void *);
void func_0011B028(void *, void *);
void func_0011AF60(void *, void *);
static inline struct Matrix *matrix_of(struct O *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_0015B420(char *p, struct O *o)
{
    void *item;
    int want;
    int kind;
    void *list;
    if (D_00479390)
        return;
    item = o->item;
    switch (o->kind) {
    case 2:
        want = 0;
        break;
    case 1:
        want = 1;
        break;
    case 0: {
        struct V4 v[4];
        int mask;
        int n = func_0015AF58(p, &mask, v);
        if (mask & ((unsigned char *)o)[0x2C]) {
            want = 1;
            if (!(func_0015B068(matrix_of(o)->rows[3], n, v) < o->range))
                want = 0;
        } else {
            want = 0;
        }
        break;
    }
    }
    list = p + 0x3DF8;
    if (want == func_0011B0C0(list, item))
        return;
    if (want) {
        func_0011AF60(list, item);
        ((void (*)(void *))o->methods[25].call)((char *)o + o->methods[25].delta);
    } else {
        ((void (*)(void *))o->methods[24].call)((char *)o + o->methods[24].delta);
        func_0011B028(list, item);
    }
}
