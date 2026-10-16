// SLY3_CFLAGS: -Os -G0
struct TriggerOwner { unsigned char opaque000[0x1A8]; int handle1A8; unsigned char opaque1AC[0x200 - 0x1AC]; int state200; };
struct TriggerParams { unsigned char opaque[0x50]; unsigned int flags; };
extern char D_00475480[];
void func_001D6110(void *owner, int state);
void func_0025D940(void *pool, int handle, int index, void *first, void *second, float gain);
int func_001D5D90(void *receiver, void *params)
{
    struct TriggerOwner *owner = (struct TriggerOwner *)receiver;
    if (((struct TriggerParams *)params)->flags & 2) {
        if (owner->state200 != 5) {
            func_001D6110(receiver, 5);
            func_0025D940(D_00475480, owner->handle1A8, -1, receiver, receiver, 1.0f);
            return 1;
        }
    }
    return 0;
}
