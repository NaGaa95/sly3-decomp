// SLY3_CFLAGS: -Os -G0
struct HeadEntry { short delta; short pad; float *(*method)(void *); };
struct HeadSelf { unsigned char prefix[0xC]; struct HeadEntry *table; unsigned char gap10[0x268-0x10]; float heading; unsigned char gap26C[0x288-0x26C]; float target; };
void func_0023D338(void *self);
float func_002A3EE8(float y,float x);
void func_0019BE08(struct HeadSelf *self)
{
    float *direction;
    float angle;
    func_0023D338(self);
    direction=self->table[36].method((char *)self+self->table[36].delta);
    angle=func_002A3EE8(direction[1],direction[0]);
    self->target=angle;
    self->heading=angle;
}
