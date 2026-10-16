// SLY3_CFLAGS: -Os -G0
struct StepLimit { unsigned char opaque[0x40]; int limit; };
struct StepOwner { unsigned char opaque00[0x30]; struct StepLimit *config; int step; };
void func_001D9A88(void *owner, int mode);
void func_00238A38(void *owner);
void func_001D9940(void *receiver)
{
    struct StepOwner *owner = (struct StepOwner *)receiver;
    owner->step = owner->step + 1;
    if (owner->step < owner->config->limit) {
        func_001D9A88(receiver, -1);
        func_001D9A88(receiver, 0);
    } else {
        func_001D9A88(receiver, -1);
        func_00238A38(receiver);
    }
}
