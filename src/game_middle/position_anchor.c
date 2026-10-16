// SLY3_CFLAGS: -Os -G0
#include "common.h"

struct AnchorMethod {
    short delta;
    short word2;
    void *target;
};

struct AnchorFrame {
    char prefix[0xC];
    struct AnchorMethod *methods;
};

struct AnchorMatrix {
    qword rows[4];
};

struct PositionAnchor {
    void *path;
    struct AnchorFrame *frame;
    int word8;
    int wordC;
    qword fixed;
};

extern char D_00474FD0[];
extern void func_0022EA88(void *, qword, void *, qword *, qword *, float *, float *);

qword func_001EE788(void *source, qword point)
{
    struct PositionAnchor *anchor = (struct PositionAnchor *)source;
    qword position;
    if (anchor->path) {
        func_0022EA88(anchor->path, point, D_00474FD0, &position, 0, 0, 0);
    } else if (anchor->frame) {
        struct AnchorFrame *frame = anchor->frame;
        struct AnchorMethod *method = &frame->methods[36];
        struct AnchorMatrix *matrix =
            ((struct AnchorMatrix *(*)(void *))method->target)
                ((char *)frame + method->delta);
        position = matrix->rows[3];
    } else {
        position = anchor->fixed;
    }
    return position;
}
