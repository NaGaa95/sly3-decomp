// SLY3_CFLAGS: -Os -G0
struct EventEntry { short delta; short pad; void (*method)(void *, int, int, int, void *, int); };
struct EventSelf { unsigned char prefix[0xC]; struct EventEntry *table; unsigned char gap10[0x50 - 0x10]; int word50; unsigned char gap54[0x70 - 0x54]; int word70; };
extern unsigned char D_00475480[];
int func_00185FD8(void *self);
void func_00186EC0(void *self, int value, int selection);
int func_0025AE28(void *game);
void func_00186FE8(void *self);
void func_00186730(struct EventSelf *self, int kind, int value)
{
    if(func_00185FD8(self)) {
        int *arguments[2];
        arguments[0] = &kind;
        arguments[1] = &value;
        self->table[3].method((char *)self + self->table[3].delta, 0x14, 0, 2, arguments, 0);
        if(!self->word70) {
            if(kind == 0xC) func_00186EC0(self, -1, 0xC);
        }
    } else {
        if(!self->word70) {
            if(kind == 0xC) {
                if(self->word50) {
                    if(!func_0025AE28(D_00475480)) func_00186FE8(self);
                }
            }
        }
    }
}
