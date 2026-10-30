// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
extern char D_00475480[];
int func_00173428(void *p);
int func_001A9478(void *g, int n);
qword func_001C9428(void *a, void *p, qword pos);
float func_001205C8(qword v);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
static inline int FBusy(char *p)
{
    return *(void **)(p + 0x1108) && func_00173428(*(void **)(p + 0x1108));
}
int func_00155B88(char *p)
{
    int r = 8;
    int dir;
    if (FBusy(p)) {
    } else if (func_001A9478(D_00475480, -1)) {
        r = 0x4000;
    } else {
        if (*(struct Object **)(p + 0x11D0)) {
            float a = func_001205C8(func_001C9428(0, p, matrix_of(*(struct Object **)(p + 0x11D0))->rows[3]));
            float m = __builtin_fabsf(a);
            if (m < 1.0f)
                dir = 0;
            else if (2.5f < m)
                dir = 3;
            else if (0.0f < a)
                dir = 1;
            else
                dir = 2;
        }
        switch (*(int *)(p + 0x11D4)) {
        case -1: case 0: break;
        case 1: r = 0x10 << dir; break;
        case 2: r = 0x100 << dir; break;
        case 3: r = 0x1000; break;
        case 4: r = 0x100; break;
        }
    }
    return r;
}
