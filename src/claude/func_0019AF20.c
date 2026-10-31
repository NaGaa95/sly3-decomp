// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Q { unsigned char pad[0x28]; unsigned long pad0 : 56; unsigned long bits : 8; };
struct P { unsigned char pad[0x1164]; int n; unsigned char pad2[0x1190 - 0x1168]; struct Q *q; };
struct A { unsigned char pad[0x10]; struct P *p; };
int func_0019AF20(struct A *a)
{
    struct P *p = a->p;
    struct Q *q;
    if (p->n)
        goto check;
fail:
    return 0;
check:
    q = p->q;
    if (!q)
        goto fail;
    if (!(q->bits & 1))
        goto fail;
    return 1;
}
