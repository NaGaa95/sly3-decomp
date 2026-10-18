// SLY3_CFLAGS: -Os -G0
struct EventOwner { unsigned char prefix[0x48]; int mode; };
struct EventTarget { unsigned char prefix[0x14]; int value; };
struct EventRecord { struct EventTarget *target; int word4; int code; unsigned char gapC[8]; int value; };
int func_001733C8(void *owner);
void func_00173280(void *owner, int mode);
void func_00173308(struct EventOwner *self, int kind, struct EventRecord *event)
{
    switch(kind) {
    case 10: {
        struct EventTarget *target = event->target;
        if(target->value == func_001733C8(self) && event->code == 0x757 && !self->mode)
            func_00173280(self, 1);
        break;
    }
    case 4:
        if(event->value == func_001733C8(self)) func_00173280(self, -1);
        break;
    }
}
