// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Pair { int a, b; };
struct Self {
    unsigned char pad0[0x2F]; unsigned long bits : 8;
    unsigned char pad30[0x1D4 - 0x30]; float speed;
    unsigned char pad1D8[0x1E4 - 0x1D8]; struct Pair saved;
};
extern unsigned char D_00475480[];
void func_0019F5F8(void *list, struct Self *self);
void func_0019F5D8(void *list, struct Self *self);
void func_0023F400(struct Self *self, void *arg);
static inline int IsActive(struct Self *self) { return self->speed != 0.0f; }
void func_0019B518(struct Self *self, void *arg)
{
    struct Pair saved;
    if (IsActive(self) && (self->bits & 1)) {
        func_0019F5F8(D_00475480, self);
    }
    saved = self->saved;
    func_0023F400(self, arg);
    self->saved = saved;
    if (IsActive(self) && (self->bits & 1)) {
        func_0019F5D8(D_00475480, self);
    }
}
