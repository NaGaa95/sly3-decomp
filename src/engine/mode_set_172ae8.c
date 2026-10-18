// SLY3_CFLAGS: -Os -G0
struct ModeOwner { unsigned char prefix[0x48]; int mode; void *source; void *current; void *pending; };
void func_00172C30(void *owner, int index);
void *func_00172A90(void *owner, int index);
void func_00172E60(void *owner, void *record);
int func_001C8610(void *source);
void func_00173280(void *owner, int mode);
void func_00172AE8(struct ModeOwner *self, int index)
{
    void *record;
    func_00172C30(self, index);
    record = func_00172A90(self, index);
    switch(self->mode) {
    case 0:
        self->pending = record;
        break;
    case 1:
        func_00172E60(self, record);
        break;
    case -1:
        if(self->current != record) {
            self->pending = record;
            if(func_001C8610(self->source)) func_00173280(self, 0);
            else func_00172E60(self, record);
        }
        break;
    }
}
