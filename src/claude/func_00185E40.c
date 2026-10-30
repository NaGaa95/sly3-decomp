// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Counters { unsigned char pad[0x4030]; int count; };
extern struct Counters D_00475480;
void func_001C7340(void *self);
void func_0011AD60(void *field, int id);
struct Self {
    unsigned char pad0[0x40]; int f40;
    unsigned char pad44[0x4C - 0x44]; int f4C;
    unsigned char pad50[0x60 - 0x50]; int f60; int f64;
    unsigned char pad68[0x80 - 0x68]; unsigned char f80[0xC];
    unsigned char f8C[0xC8 - 0x8C]; int fC8; int fCC;
    unsigned char padD0[0xF8 - 0xD0]; int fF8;
};
void func_00185E40(struct Self *self)
{
    func_001C7340(self);
    self->f60 = -1;
    self->f64 = -1;
    func_0011AD60(self->f80, 0x74);
    func_0011AD60(self->f8C, 0x4C);
    self->f4C = -1;
    self->f40 = -1;
    self->fC8 = -1;
    self->fCC = -1;
    self->fF8 = -1;
    D_00475480.count++;
}
