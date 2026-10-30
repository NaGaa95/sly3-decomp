// SLY3_CFLAGS: -Os -G0
struct FlagSelf { unsigned char prefix[0x28]; unsigned long flags; };
void *func_0015D0B8(struct FlagSelf *self)
{
    void *r = 0;
    if (self->flags & (1UL << 60))
        r = self ? (char *)self + 0x210 : 0;
    return r;
}
