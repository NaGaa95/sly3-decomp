// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; int f; char pad2[0x1B0 - 0x40]; int on; };
void func_0014E938(struct S *s, int on)
{
    if (on == s->on)
        return;
    s->on = on;
    if (on) {
        int v = s->f;
        if ((v ^ 1) & 1)
            *(int *)v |= 2;
        else
            s->f = v | 2;
    } else {
        int v = s->f;
        if ((v ^ 1) & 1)
            *(int *)v &= ~2;
        else
            s->f = v & ~2;
    }
}
