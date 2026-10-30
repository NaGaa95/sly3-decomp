// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self { unsigned char pad[0xF0]; int grf; };
struct Other { unsigned char pad[0x164]; int grf; };
void func_001A1FF0(struct Self *self, struct Other *other)
{
    self->grf |= other->grf;
}
