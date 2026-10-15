// Preserve the explicit128-bit input across the slot lookup and assign it to the returned slot.
// Reference algorithm: src/hand/func_00120CC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { float values[4]; } __attribute__((aligned(16)));
struct V *func_0022F450(void *object,int selector);
void func_0022F638(void *object,const struct V *source)
{
    struct V copy=*source;
    *func_0022F450(object,1)=copy;
}
