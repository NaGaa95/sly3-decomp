// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self { unsigned char pad[0xF8]; unsigned char fF8[1]; };
void func_001C81B8(struct Self *self);
void func_0015CE68(void *p);
void func_001A1FC0(struct Self *self)
{
    func_001C81B8(self);
    func_0015CE68(self->fF8);
}
