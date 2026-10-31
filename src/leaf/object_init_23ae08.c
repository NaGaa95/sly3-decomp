// SLY3_CFLAGS: -Os -G0
// Object defaults: base init, a 0x24-entry list, scalar defaults, and flag bit 3 inherited from the owner (set when there is none).
struct Object {
    unsigned char pad00[0x10]; struct Object *owner;
    unsigned char pad14[0x54 - 0x14]; unsigned char list54[0x104 - 0x54];
    float f104; unsigned char pad108[0x114 - 0x108];
    float f114; int f118; unsigned char pad11C[0x124 - 0x11C];
    unsigned char b124, b125; unsigned char pad126[2];
    unsigned long flags;
};
void func_001C7340(void *self);
void func_001C9118(void *self, int value);
void func_0011AF38(void *list, int count);
void func_0023AE08(struct Object *self)
{
    int inherited;
    func_001C7340(self);
    func_001C9118(self, 0);
    func_0011AF38(self->list54, 0x24);
    self->f104 = 1.0f;
    self->b124 = 10;
    self->b125 = 20;
    self->f114 = 400.0f;
    if (self->owner)
        inherited = (int)(self->owner->flags >> 3) & 1;
    else
        inherited = 1;
    self->flags = (self->flags & ~8UL) | ((unsigned long)inherited << 3) | 0x100;
    self->f118 = -1;
}
