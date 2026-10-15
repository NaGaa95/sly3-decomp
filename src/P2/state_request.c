// SLY3_CFLAGS: -Os -G0
#include "position_attachment_api.h"

typedef struct StateMatrix { SequencePackedPosition rows[4]; } StateMatrix;
typedef struct StateVirtualEntry {
    short this_delta;
    short unused;
    StateMatrix *(*matrix)(void *);
} StateVirtualEntry;
typedef struct StateActor {
    char prefix[0xC];
    StateVirtualEntry *vtable;
    char before_identifier[0x130 - 0x10];
    int identifier;
    char before_state[0x112C - 0x134];
    int state;
} StateActor;
typedef struct StateController {
    char prefix[0x10];
    StateActor *actor;
    char before_mode[0x30 - 0x14];
    int mode;
} StateController;
typedef struct StateRequest {
    int kind;
    void *payload;
    float value;
    unsigned int unused;
} StateRequest;
extern char D_00475480[];
extern float D_00321EAC;
void *func_00292034(void *,int,unsigned int);
int func_0013B500(void *,int);
void *func_001F4AD0(void *,int);
int func_0019AED0(StateController *);
int func_0019AF20(StateController *);
int func_0019AF98(StateController *,StateRequest *);
void func_0019A2D0(StateController *,StateRequest *);

void func_0019AD90(StateController *controller)
{
    StateRequest request;
    func_00292034(&request,0,sizeof(request));
    if (controller->actor->identifier != -1 &&
        func_0013B500(controller->actor,0x3C)) {
        request.kind = 0x14;
    } else if (controller->actor->state == 0x14) {
        request.kind = 0x10;
        request.payload = func_001F4AD0(D_00475480,0);
        request.value = D_00321EAC;
    } else if (func_0019AED0(controller)) {
        request.kind = 0xC;
    } else if (func_0019AF20(controller)) {
        request.kind = 0x12;
    } else if (!func_0019AF98(controller,&request)) {
        int mode = controller->mode;
        if (mode < 11) {
            if (mode >= 6) {
                request.kind = 2;
                request.payload = func_00173E00(D_00475480,0,
                    controller->actor->vtable[36].matrix(
                        (char *)controller->actor + controller->actor->vtable[36].this_delta)->rows[3],
                    (int)controller->actor);
            } else {
                request.kind = 1;
            }
        } else {
            request.kind = 1;
        }
    }
    func_0019A2D0(controller,&request);
}
