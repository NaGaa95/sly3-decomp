// SLY3_CFLAGS: -Os -G0
struct StateEntry { short delta; short pad; void (*method)(void *); };
struct StateRecord { unsigned char prefix[0xC]; struct StateEntry *table; unsigned char gap10[0x3C - 0x10]; int value; };
struct StateOwner { unsigned char prefix[0x29C]; unsigned char list[0x10D0 - 0x29C]; void *queue; };
struct StateSelf { unsigned char prefix[0x10]; struct StateOwner *owner; unsigned char gap14[0x18 - 0x14]; unsigned char slot[0x30 - 0x18]; int state; float stamp; int word38; };
extern float D_0036BB98;
extern const int D_0031F828[];
void func_00238AE8(void *slot);
void func_00238AB8(void *self);
struct StateRecord *func_00238690(void *list, int kind);
void func_001703C8(void *queue, int value, int flag);
void func_002541F8(void *owner, int selected);

extern float D_0036BB90[];
void func_00134860(struct StateSelf *self, int state)
{
    if(state == self->state) return;
    func_00238AE8(self->slot);
    self->state = state;
    self->stamp = D_0036BB90[2];
    switch(state) {
    case 0: case 1: case 2: case 3: case 4: case 5: {
        struct StateRecord *record = func_00238690(self->owner->list, 0xC9);
        record->value = D_0031F828[self->state];
        record->table[8].method((char *)record + record->table[8].delta);
        if(self->state == 5) {
            func_001703C8(self->owner->queue, self->word38, 0);
            func_002541F8(self->owner, 0);
        }
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
