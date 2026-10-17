// SLY3_CFLAGS: -Os -G0
struct MachineSelf {
    unsigned char prefix[0x10]; void *owner;
    unsigned char gap14[0x30 - 0x14]; int value; int state; int gap38; int pending;
};
void func_002389A0(void *self);
int func_00238AD0(void *self);
int func_00238AA8(void *self);
int func_00135758(void *self);
void func_001355C8(void *self, int mode);
void func_0024E920(void *owner, int value);
void func_001354A8(struct MachineSelf *self)
{
    int previous;
    func_002389A0(self);
    do {
        previous = self->state;
        switch(previous) {
        case 0:
            if(func_00238AD0(self)) func_001355C8(self, 1);
            break;
        case 1:
            if(!func_00238AA8(self)) {
                int found = func_00135758(self);
                if(found) {
                    self->pending = found;
                    func_001355C8(self, 2);
                }
            }
            break;
        case 2:
            if(func_00238AD0(self) && !func_00238AA8(self)) func_001355C8(self, 1);
            break;
        case 3:
            if(func_00238AD0(self)) func_001355C8(self, -1);
            break;
        }
    } while(previous != self->state);
    func_0024E920(self->owner, self->value);
}
