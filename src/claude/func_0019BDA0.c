// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self {
    unsigned char pad0[0x1F0]; int state;
    unsigned char pad1F4[0x1F8 - 0x1F4]; unsigned char block[0x284 - 0x1F8]; int count;
    unsigned char pad288[0x304 - 0x288]; int target;
    unsigned char pad308[0x310 - 0x308]; float near; float far;
};
void func_0019B420(struct Self *self);
void func_0019B940(struct Self *self, int kind, void *block);
void func_0019BDA0(struct Self *self)
{
    func_0019B420(self);
    func_0019B940(self, 7, self->block);
    self->state = -1;
    self->count = 0;
    self->target = -1;
    self->near = 1250.0f;
    self->far = 2500.0f;
}
