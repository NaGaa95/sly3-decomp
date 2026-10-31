// SLY3_CFLAGS: -O2 -G0 -ffast-math
struct MenuItem { unsigned char pad00[0xC]; void *owner; };
void func_0016FA08(void *owner, void *item);
void func_001D4DE8(struct MenuItem *item)
{
    func_0016FA08(item->owner, item);
}
