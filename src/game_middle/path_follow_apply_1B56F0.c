// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct FollowMethod { short adjustment, word2; void *function; };
struct FollowTable {
    unsigned char prefix[0x120];
    struct FollowMethod matrix;
    unsigned char gap128[0x2E8 - 0x128];
    struct FollowMethod apply;
};
struct FollowMatrix { unsigned char prefix[0x30]; qword position; };
struct FollowActor {
    unsigned char prefix0[0xC];
    struct FollowTable *methods;
    unsigned char gap10[0x240 - 0x10];
    qword anchor;
};
struct FollowPath { unsigned char prefix0[0xC]; struct FollowTable *methods; unsigned char gap10[0x1CC - 0x10]; int curved; };
struct FollowControl {
    struct FollowActor *actor;
    unsigned char gap4[4];
    int mode;
    unsigned char gapC[0x14 - 0xC];
    struct FollowPath *path;
    unsigned char gap18[4];
    float progress;
    float length;
};
extern qword D_00317540;
qword func_00250600(void *actor);
void func_0022EA50(void *path, qword anchor, int kind, void *position, void *direction, float *progress, float *length, float initial);
void func_0022E148(void *path, void *position, void *direction, float t);
void func_001B56F0(struct FollowControl *control)
{
    switch (control->mode) {
    case 4: {
        struct FollowMethod *matrix = &control->path->methods->matrix;
        qword position = ((struct FollowMatrix *(*)(void *))matrix->function)((char *)control->path + matrix->adjustment)->position;
        qword anchor = func_00250600(control->actor);
        struct FollowMethod *apply = &control->actor->methods->apply;
        ((void (*)(void *, int, void *, qword, qword, qword))apply->function)(
            (char *)control->actor + apply->adjustment, 7, control->path, position, D_00317540, anchor);
        control->actor->anchor = anchor;
        break;
    }
    case 3: {
        struct FollowPath *path = control->path;
        qword anchor = func_00250600(control->actor);
        qword position, direction;
        int kind;
        struct FollowMethod *apply;
        if (path->curved) {
            func_0022EA50(path, anchor, 0, &position, &direction, &control->progress, &control->length, control->progress);
            kind = 6;
        } else {
            func_0022E148(path, &position, &direction, control->progress);
            kind = 7;
        }
        apply = &control->actor->methods->apply;
        ((void (*)(void *, int, void *, qword, qword, qword))apply->function)(
            (char *)control->actor + apply->adjustment, kind, path, position, direction, anchor);
        control->actor->anchor = anchor;
        break;
    }
    }
}
