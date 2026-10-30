// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { int a; float g; int b, c; };
int func_00174C58(struct E **ppa, struct E **ppb)
{
    struct E *pa = *ppa;
    struct E *pb = *ppb;
    if (pb->g < pa->g)
        return -1;
    if (pa->g < pb->g)
        return 1;
    return pa - pb;
}
int func_00174CA0(struct E **ppa, struct E **ppb)
{
    struct E *pa = *ppa;
    struct E *pb = *ppb;
    if (pb->g < pa->g)
        return 1;
    if (pa->g < pb->g)
        return -1;
    return pb - pa;
}
