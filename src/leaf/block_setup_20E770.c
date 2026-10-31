// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct BlockSource { int type; float scale; int extra; };
struct BlockSelf {
    unsigned char prefix0[0x10];
    struct { unsigned char pad[0x10]; void *target; } *owner;
    unsigned char gap14[0xF0 - 0x14];
    void *handle;
    float scale;
    int count;
    void *blocks[8];
};
extern char D_00475480[];
void func_0020BDA8(void *self, struct BlockSource *source);
void *func_0017E1B8(void *world, int kind, int type, void *target);
void *func_0011E118(void *pool);
void func_0020E5F0(struct BlockSelf *self);
void func_0020E770(struct BlockSelf *self, struct BlockSource *source)
{
    func_0020BDA8(self, source);
    self->handle = func_0017E1B8(D_00475480, 4, source->type, self->owner->target);
    self->scale = source->scale;
    self->blocks[self->count++] = func_0011E118(D_00475480 + 0x45AC);
    if (source->extra) {
        self->blocks[self->count++] = func_0011E118(D_00475480 + 0x45AC);
        self->blocks[self->count++] = func_0011E118(D_00475480 + 0x45AC);
    }
    func_0020E5F0(self);
}
