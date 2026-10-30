// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Counters { unsigned char pad[0x402C]; int count; };
extern struct Counters D_00475480;
void func_001C7340(void *self);
struct Self {
    unsigned char pad0[0x44]; int f44;
    unsigned char pad48[0x4C - 0x48]; int f4C;
    unsigned char pad50[0xA8 - 0x50]; int fA8; int fAC; int fB0; int fB4;
    float fB8; float fBC; int fC0;
    unsigned char padC4[0xF8 - 0xC4]; int fF8; int fFC;
};
void func_00187E90(struct Self *self)
{
    func_001C7340(self);
    self->fB8 = 240.0f;
    self->fBC = 360.0f;
    self->f44 = -1;
    self->fF8 = -1;
    self->f4C = -1;
    self->fFC = 0;
    self->fA8 = -1;
    self->fAC = -1;
    self->fB0 = -1;
    self->fB4 = -1;
    self->fC0 = -1;
    D_00475480.count++;
}
