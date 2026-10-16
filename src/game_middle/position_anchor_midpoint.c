// SLY3_CFLAGS: -Os -G0
#include "common.h"

struct MidpointMethod {
    short delta;
    short word2;
    void *target;
};

struct MidpointFrame {
    char prefix[0xC];
    struct MidpointMethod *methods;
};

struct MidpointMatrix {
    qword rows[4];
};

struct MidpointAnchor {
    void *path;
    struct MidpointFrame *frame;
    int word8;
    int wordC;
    qword fixed;
};

extern float func_0022DFD8(void *);
extern void func_0022E330(void *, qword *, qword *, float);

qword func_001EE7F8(void *source)
{
    struct MidpointAnchor *anchor = (struct MidpointAnchor *)source;
    qword position;
    if (anchor->path) {
        func_0022E330(anchor->path, &position, 0,
                     func_0022DFD8(anchor->path) * 0.5f);
    } else if (anchor->frame) {
        struct MidpointFrame *frame = anchor->frame;
        struct MidpointMethod *method = &frame->methods[36];
        struct MidpointMatrix *matrix =
            ((struct MidpointMatrix *(*)(void *))method->target)
                ((char *)frame + method->delta);
        position = matrix->rows[3];
    } else {
        position = anchor->fixed;
    }
    return position;
}
