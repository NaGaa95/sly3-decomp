// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
struct S { qword pos; char pad10[0x54 - 0x10]; float g54; int pad58; float g5C; char pad60[0x6C - 0x60]; int flags; };
void func_00250690(void *p, struct S *s);
void func_001BFA18(void *a, struct S *s);
void func_001BD758(void *a, struct S *s);
void func_001ABBF0(void *a, struct S *s);
void func_001C3D78(void *a, struct S *s);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00153D40(char *p, struct S *s)
{
    func_00250690(p, s);
    s->g54 = 100.0f;
    s->g5C = *(float *)(p + 0x1154);
    s->pos = matrix_of((struct Object *)p)->rows[3];
    if (*(int *)(p + 0x218) || *(int *)(p + 0x508) == 3 || *(int *)(p + 0x508) == 4) {
        ((float *)&s->pos)[2] = *(float *)(p + 0x248) + *(float *)(p + 0x1158);
    } else {
        ((float *)&s->pos)[2] += *(float *)(p + 0x268) + *(float *)(p + 0x1158);
        if (*(int *)(p + 0x33C) != 0x12 && *(int *)(p + 0x33C) != 0x15)
            s->flags |= 4;
    }
    if (*(int *)(p + 0x1150))
        s->flags |= 2;
    if (*(int *)(p + 0x1014) != -1)
        func_001BFA18(p + 0x1010, s);
    if (*(int *)(p + 0x33C) != -1)
        func_001BD758(p + 0x320, s);
    if (*(int *)(p + 0x50C) != -1)
        func_001ABBF0(p + 0x500, s);
    if (*(int *)(p + 0xE44) != -1)
        func_001C3D78(p + 0xE40, s);
    if (*(int *)(p + 0x1014) != -1)
        func_001BFA18(p + 0x1010, s);
}
