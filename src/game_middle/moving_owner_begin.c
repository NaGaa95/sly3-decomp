// SLY3_CFLAGS: -Os -G0
typedef unsigned int MovingPosition __attribute__((mode(TI)));
struct MovingOwner {
    unsigned char opaque00[0x4C];
    void *controller;
    unsigned char opaque50[0x200 - 0x50];
    MovingPosition position;
    void *animation;
    void *animationInstances[12];
    int actionEnabled;
    void *action;
    float parameter;
};
void func_001D6D20(void *receiver, void *owner);
void func_00137588(void *animation, void *receiver, float start, float weight,
                  int flags, void **instances);
void *func_00130190(void *receiver, void *controller, int mode, int flags,
                   float parameter, float weight);

void func_001D6C98(struct MovingOwner *receiver, void *owner, MovingPosition position)
{
    func_001D6D20(receiver, owner);
    receiver->position = position;
    func_00137588(receiver->animation, receiver, 0.0f, 1.0f,
                  8, receiver->animationInstances);
    if (receiver->actionEnabled)
        receiver->action = func_00130190(receiver, receiver->controller,
                                        0, 5, receiver->parameter, 0.0f);
}
