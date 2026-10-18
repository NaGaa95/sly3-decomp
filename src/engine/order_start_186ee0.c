// SLY3_CFLAGS: -Os -G0
struct StartObject { unsigned char prefix[0xB8]; int busy; unsigned char gapBC[0xC4 - 0xBC]; void *record; int first; int second; };
extern unsigned char D_00475480[];
extern unsigned char D_0036C700[];
void func_001878E0(void *object, int mode);
void *func_0017E1B8(void *game, int kind, int id, void *owner);
void func_001854C8(void *table, int slot, void *object);
void func_00186F90(void *object);
void func_00186EE0(struct StartObject *self, int first, int id, int second)
{
    if(!self->busy) {
        func_001878E0(self, 9);
        self->first = first;
        self->record = func_0017E1B8(D_00475480, 4, id, self);
        self->second = second;
        func_001854C8(D_0036C700, 0x20, self);
        if(self->record) func_001878E0(self, 4);
        else func_00186F90(self);
    }
}
