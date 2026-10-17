// SLY3_CFLAGS: -Os -G0
struct PickMethod { short adjustment, word2; void *function; };
struct PickTable { unsigned char prefix[0x280]; struct PickMethod accept; };
struct PickInner { unsigned char prefix[0x14]; void *id; };
struct PickObject { unsigned char prefix[0x1E8]; struct PickInner *inner; };
struct PickRequest {
    unsigned char prefix0[0x14];
    struct PickObject *object;
    unsigned char gap18[0x20 - 0x18];
    int word20;
    int word24;
    int word28;
    unsigned char gap2C[0x50 - 0x2C];
    unsigned int flags;
};
struct PickSelf {
    unsigned char prefix0[0xC];
    struct PickTable *methods;
    unsigned char gap10[4];
    void *id;
    unsigned char gap18[0x1BC - 0x18];
    float restart;
    unsigned char gap1C0[0x1C8 - 0x1C0];
    float cooldown;
    int state;
};
extern float D_00325B10;
extern unsigned char D_0036C700[];
int func_0013B500(void *object, int kind);
void func_001F4DD8(void *receiver, void *object, int selection, float time);
void func_001F43D0(void *receiver, int value);
int func_001F43C8(void *receiver);
void func_0020F868(void *receiver, int state);
void func_001854C8(void *context, int event, void *owner);
int func_0020F5F0(struct PickSelf *self, struct PickRequest *request)
{
    struct PickMethod *method;
    if (self->cooldown > 0.0f)
        return 0;
    method = &self->methods->accept;
    if (((int (*)(void *, int))method->function)((char *)self + method->adjustment, request->word20))
        return 0;
    if (self->state != 2)
        return 0;
    if (func_0013B500(request->object, 0x59)) {
        if (request->object->inner->id == self->id)
            return 0;
    }
    if (!(request->flags & 2))
        return 0;
    func_001F4DD8(self, request->object, request->word20, D_00325B10);
    if (request->word28)
        func_001F43D0(self, 0);
    else
        func_001F43D0(self, func_001F43C8(self) - request->word24);
    if (func_001F43C8(self) <= 0) {
        func_0020F868(self, 3);
    } else {
        func_001854C8(D_0036C700, 10, self);
        self->cooldown = self->restart;
    }
    return 1;
}
