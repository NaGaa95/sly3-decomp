// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Node { qword pos; qword rel; char pad[0x64 - 0x20]; struct Node *next; };
struct Object {
    unsigned char pad00[0xC];
    struct Method *methods;
    unsigned char pad10[0x148];
    struct Node *nodes;
    unsigned char pad15C[0x1150 - 0x15C];
    int state;
};
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
void func_00153EA0(struct Object *o, int state)
{
    struct Node *n;
    if (state == o->state)
        return;
    o->state = state;
    if (state)
        return;
    for (n = o->nodes; n; n = n->next) {
        qword pos = n->pos;
        qword r;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(pos), "j"(matrix_of(o)->rows[3]));
        n->rel = r;
        ((int *)&n->rel)[2] = 0;
    }
}
