// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Matches 0x1A9568-0x1A95C8 exactly; 0x1A95C8 'slt v0,zero,v1' + 0x1A95CC nop is an unreachable trailing
   fragment after jr (same family as 0x169E80 / 0x18C218 / 0x1A7978) that needs an exclusion entry. */
struct Player { unsigned char storage[0x11C0]; };
extern struct Player D_0036E740[];
int func_001A9538(void *self, int kind);
int func_001F4B30(struct Player *p);
int func_001A9568(void *self, int kind)
{
    if (func_001A9538(self, kind))
        return 0;
    if (kind == 0)
        return 1;
    if (kind == 1) {
        if (func_001F4B30(&D_0036E740[kind]))
            return 1;
    }
    return 0;
}
