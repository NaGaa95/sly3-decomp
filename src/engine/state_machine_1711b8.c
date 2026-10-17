// SLY3_CFLAGS: -Os -G0
struct MachineItem { unsigned char prefix[0x130]; int state; };
struct MachineSelf { unsigned char prefix[0x134]; void *handle; unsigned char gap138[0x190 - 0x138]; int state; unsigned char gap194[0x1A4 - 0x194]; int count; struct MachineItem *items[4]; unsigned char gap1B8[0x1C8 - 0x1B8]; int flag1C8; int flag1CC; };
void func_0023C660(void *self);
void func_00171538(void *self, int value);
void func_00171358(void *self);
int func_001A7A80(void *handle, float limit, int mask);
int func_00171868(void *self);
void *func_002459F8(int id);
void func_00244F08(void *sound, int flag);
void func_001711B8(struct MachineSelf *self)
{
    int state;
    func_0023C660(self);
    do {
        state = self->state;
        switch(state) {
        case 0:
            break;
        case 1: {
            int all = 1;
            int i;
            for(i = 0; i < self->count; i++) {
                if(self->items[i]->state == 2) { all = 0; break; }
            }
            if(all) func_00171538(self, 0);
            break;
        }
        case 3:
            func_00171538(self, self->flag1C8 != 0);
            break;
        case 2:
            if(func_001A7A80(self->handle, 0.15f, 0x10)) {
                func_00171538(self, 3);
            } else {
                int r = func_001A7A80(self->handle, 0.15f, 0x20);
                if(r && !self->flag1CC) {
                    if(func_00171868(self)) func_00171538(self, 0);
                    else func_00244F08(func_002459F8(0x3E), 0);
                } else if((r || self->flag1CC) && func_00171868(self)) {
                    func_00171538(self, 0);
                } else {
                    func_00171358(self);
                }
            }
            break;
        }
    } while(self->state != state);
}
