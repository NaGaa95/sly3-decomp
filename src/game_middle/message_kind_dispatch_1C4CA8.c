// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct MessageTable {
    unsigned char prefix0[0x48];
    struct Method finish;
    unsigned char prefix1[0x280 - 0x50];
    struct Method begin;
    struct Method state;
};
struct MessageTarget {
    unsigned char prefix[0xC];
    struct MessageTable *methods;
};
extern char D_0036C700[];
extern qword D_00317560;
int func_0013B500(void *object, int kind);
void func_001854C8(void *context, int event, void *owner);
void func_0014CB98(void *self, float value);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);
void func_001C4CA8(void *receiver, struct MessageTarget *target)
{
    if (func_0013B500(target, 0x31)) {
        struct Method *state = &target->methods->state;
        if (((int (*)(void *))state->function)((char *)target + state->adjustment) != 2)
            func_001854C8(D_0036C700, 0x5F, target);
    }
    if (func_0013B500(target, 0x59)) {
        func_0014CB98(target, 0.0f);
    } else if (func_0013B500(target, 0x71)) {
        struct Method *begin = &target->methods->begin;
        struct Method *finish;
        ((void (*)(void *, int))begin->function)((char *)target + begin->adjustment, -1);
        finish = &target->methods->finish;
        ((void (*)(void *))finish->function)((char *)target + finish->adjustment);
    } else if (func_0013B500(target, 0x2F)) {
        func_00240CB0(receiver, 0, target, 0x4000, 0x1F4, 1, D_00317560, D_00317560, 0);
    }
}
