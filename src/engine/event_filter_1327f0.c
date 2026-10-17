// SLY3_CFLAGS: -Os -G0
struct FilterSelf { unsigned char prefix[0x40]; void *source; unsigned char gap44[0xD0 - 0x44]; int pending; };
int func_00254F80(void *source);
void func_00132C58(void *self, int mode);
void func_001328B0(void *self);
int func_00131850(void *self, int event, int *message);
int func_001327F0(struct FilterSelf *self, int event, int *message)
{
    if(event == 10 && self->source && message[0] == func_00254F80(self->source)) {
        switch(message[2]) {
        case 0x3D:
            if(!self->pending) func_00132C58(self, 1);
            return 1;
        case 0x4D:
            func_001328B0(self);
            return 1;
        }
    }
    return func_00131850(self, event, message);
}
