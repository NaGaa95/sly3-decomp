// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
extern char *D_00479B5C;
extern char *D_00479B80;
int func_00156998(void *p);
void *func_001738C0(void *a, qword pos, void *p);
int func_002533C0(void *o, int kind);
int func_00174238(void *o, void *h);
void func_002BC618(void *buf, int n);
void func_001739A8(void *h);
void func_002BC5F0(void *buf, int n);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return (struct Matrix *)method->call((unsigned char *)object + method->delta);
}
int func_00153158(char *p)
{
    char buf[16];
    void *h;
    int r;
    char *o;
    if (func_00156998(p))
        return 2;
    h = 0;
    if (*(void **)(p + 0x119C))
        h = func_001738C0(*(void **)(p + 0x119C), matrix_of((struct Object *)p)->rows[3], p);
    if (!h)
        return 2;
    r = 0;
    for (o = D_00479B5C; o; o = *(char **)(o + 0x113C)) {
        struct Object *ob = (struct Object *)o;
        if (func_002533C0(o, 0x31) || func_002533C0(o, 0x11)) { r = 2; break; }
        if (((int (*)(void *, void *))ob->methods[98].call)(o + ob->methods[98].delta, h)) { r = 1; break; }
    }
    if (!r) {
        for (o = D_00479B80; o; o = *(char **)(o + 0xF4)) {
            if (func_00174238(o, h)) { r = 1; break; }
        }
        func_002BC618(&buf[1], 2);
    }
    func_001739A8(h);
    func_002BC5F0(buf, 2);
    return r;
}
