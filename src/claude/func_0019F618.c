// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Self {
    unsigned char pad0[0x2F]; unsigned long bits : 8;
    unsigned char pad30[0x1D4 - 0x30]; float speed;
};
extern unsigned char D_00475480[];
void func_0019F5F8(void *list, struct Self *self);
void func_0019F5D8(void *list, struct Self *self);
static inline int IsActive(struct Self *self) { return self->speed != 0.0f; }
void func_0019F618(struct Self *self, float speed)
{
    if (IsActive(self) && (self->bits & 1)) {
        func_0019F5F8(D_00475480, self);
    }
    self->speed = speed;
    if (IsActive(self) && (self->bits & 1)) {
        func_0019F5D8(D_00475480, self);
    }
}
