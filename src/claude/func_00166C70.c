// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { char pad[0xD4]; int xD4; char pad1[0x100 - 0xD8]; int x100; float g104; char pad2[0x110 - 0x108]; };
int func_00166C70(struct E **ppa, struct E **ppb)
{
    struct E *pa = *ppa;
    struct E *pb = *ppb;
    int d = pb->x100 - pa->x100;
    if (d != 0)
        return d;
    d = pb->xD4 - pa->xD4;
    if (d != 0)
        return d;
    if (pa->g104 < pb->g104)
        return -1;
    if (pb->g104 < pa->g104)
        return 1;
    return pa - pb;
}
