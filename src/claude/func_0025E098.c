// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Find the slot holding an equal handle (cf. Sly 2 src/hand/func_002109D0.c).
struct X { int x0; int x4; int x8; char padc[0x38 - 0xC]; int x38; int x3C; };
struct X *func_0025E070(int i);
static inline int FInvalid(struct X *a)
{
    int f = 0;
    if (!a || a->x4 == a->x3C) {
        f = 1;
    }
    return f;
}
static inline int FEqual(struct X *a, struct X *b)
{
    if (a == b)
        return 1;
    if (!a || !b)
        return 0;
    return (a->x8 ^ a->x38) == (b->x8 ^ b->x38);
}
int func_0025E098(struct X *px)
{
    int i;
    if (FInvalid(px))
        return -1;
    for (i = 0; i < 40; i++) {
        if (FEqual(px, func_0025E070(i)))
            return i;
    }
    return -1;
}
