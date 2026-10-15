// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "activation_selector_api.h"
#include "../P2/input_mask.h"
typedef int qword __attribute__((mode(TI)));
struct ActorSecondary {
    unsigned char opaque00[0x48];
    void *first_frame, *second_frame;
    unsigned char opaque50[0x1A0 - 0x50];
    qword direction;
    unsigned char opaque1B0[0x113C - 0x1B0];
    void *animation, *request;
    unsigned char opaque1144[0x1760 - 0x1144];
    void *resource;
    unsigned char opaque1764[0x1870 - 0x1764];
    void *sequence;
    int state;
    float time;
};
extern "C" {
extern qword D_00317560;
void func_0028F068(void *actor, void *frame, int mode);
void func_00137628(void **animation);
void func_0023AC58(void **request);
void func_00137588(void *sequence, void *actor, float time, float rate,
    int mode, void **animation);
void func_001DE398(struct ActorSecondary *actor, int state)
{
    void *sequence;
    void *resource;
    int mode;
    if (state == actor->state) return;
    if (actor->state == 0) {
        func_0028F068(actor, actor->first_frame, 2);
        func_0028F068(actor, actor->second_frame, 2);
    }
    actor->state = state;
    actor->time = D_0036BB98.now;
    sequence = 0;
    resource = 0;
    mode = 1;
    switch (state) {
    case 0:
        func_0028F068(actor, actor->first_frame, 1);
        func_0028F068(actor, actor->second_frame, 1);
        resource = actor->resource;
        actor->direction = D_00317560;
        break;
    case 1:
        sequence = actor->sequence;
        mode = 9;
        break;
    }
    func_00137628(&actor->animation);
    func_0023AC58(&actor->request);
    func_00137588(sequence, actor, 0.0f, 1.0f, mode, &actor->animation);
    func_0023AAE8(resource, actor, -1, mode, &actor->request);
}
}
