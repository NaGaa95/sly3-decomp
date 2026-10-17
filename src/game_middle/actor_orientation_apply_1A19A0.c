// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct OrientationRows { qword r[3]; };
struct OrientationMethod { short adjustment, word2; void *(*function)(void *self); };
struct OrientationTable { unsigned char prefix[0x120]; struct OrientationMethod matrix; };
struct OrientationActor {
    unsigned char prefix[0xC];
    struct OrientationTable *methods;
    unsigned char gap10[0x178 - 0x10];
    int blocked;
    unsigned char gap17C[0x188 - 0x17C];
    int enabled;
};
extern qword D_00317560;
extern char D_003221A0[], D_003221B0[];
void func_00243738(void *actor);
void func_0011CCF8(void *input, void *optional, struct OrientationRows *output);
void func_0023EFA0(void *actor, struct OrientationRows *rotation, void *first, qword vector, void *second);
void func_001A19A0(struct OrientationActor *actor)
{
    func_00243738(actor);
    if (actor->enabled && !actor->blocked) {
        struct OrientationRows rotation;
        struct OrientationMethod *method = &actor->methods->matrix;
        func_0011CCF8(method->function((char *)actor + method->adjustment), 0, &rotation);
        func_0023EFA0(actor, &rotation, D_003221A0, D_00317560, D_003221B0);
    }
}
