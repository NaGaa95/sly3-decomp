// SLY3_CFLAGS: -Os -G0
struct StateEntry { short delta; short pad; void (*method)(void *); };
struct StateRecord { unsigned char prefix[0xC]; struct StateEntry *table; unsigned char gap10[0x38 - 0x10]; int word38; int value; unsigned char gap40[0xA4 - 0x40]; int flag; };
struct StateOwner { unsigned char prefix[0x29C]; unsigned char list[1]; };
struct StateSelf { unsigned char prefix[0x10]; struct StateOwner *owner; unsigned char gap14[0x18 - 0x14]; unsigned char slot[0x30 - 0x18]; int state; float stamp; int word38; };
extern float D_0036BB90[];
void func_00238AE8(void *slot);
void func_00238AB8(void *self);
struct StateRecord *func_00238690(void *list, int kind);
void func_0017FCF0(void *self);

void func_0017FE90(struct StateSelf *self, int state)
{
    if(state == self->state) return;
    func_00238AE8(self->slot);
    self->state = state;
    self->stamp = D_0036BB90[2];
    switch(state) {
    case 0: {
        struct StateRecord *record = func_00238690(self->owner->list, 0xC9);
        record->value = 0x11;
        record->word38 = self->word38;
        record->table[8].method((char *)record + record->table[8].delta);
        break;
    }
    case 1: {
        struct StateRecord *record = func_00238690(self->owner->list, 0xE1);
        record->flag = 1;
        record->word38 = 0x30;
        func_0017FCF0(self);
        record->table[8].method((char *)record + record->table[8].delta);
        break;
    }
    case 2: {
        struct StateRecord *record = func_00238690(self->owner->list, 0xCA);
        record->value = 1;
        record->table[8].method((char *)record + record->table[8].delta);
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
