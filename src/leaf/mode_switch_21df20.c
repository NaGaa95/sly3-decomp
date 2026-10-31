// Switch the controller to a new mode, refreshing the ramp values for mode 1 and choosing the matching effect id for modes 2, 5 and 6.
// SLY3_CFLAGS: -Os -G0
struct Method { short delta, reserved; void (*call)(void *); };
struct Object {
    unsigned char opaque00[0xC];
    struct Method *methods;
    unsigned char opaque10[0x120 - 0x10];
    float current0;
    float target0;
    float current1;
    float target1;
    unsigned char opaque130[8];
    int mode;
    unsigned char opaque13C[4];
    int slot;
    int previous;
};
void func_0021E028(struct Object *self);
void func_00262450(struct Object *self, int id);
void func_00261580(struct Object *self, int id, float value);
void func_00262B60(struct Object *self, int id, int *slot);

void func_0021DF20(struct Object *self, int mode)
{
    int id;
    if (self->mode == mode) return;
    if (self->mode == -1) self->previous = self->mode;
    self->mode = mode;
    id = -1;
    switch (mode) {
    case -1:
        self->methods[54].call((char *)self + self->methods[54].delta);
        break;
    case 1:
        func_0021E028(self);
        self->current0 = self->target0;
        self->current1 = self->target1;
        func_00262450(self, 0x3CA);
        func_00261580(self, 0x3CA, self->current0);
        func_00262450(self, 0x3CB);
        func_00261580(self, 0x3CB, self->current1);
        break;
    case 2:
        id = 0x3C4;
        break;
    case 5:
        id = 0x3C5;
        break;
    case 6:
        id = 0x3C6;
        break;
    }
    func_00262B60(self, id, &self->slot);
}
