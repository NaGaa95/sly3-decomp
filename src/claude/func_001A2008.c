// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0xF0]; int fl; };
void func_001A2008(struct S *p, int n)
{
    switch (n) {
    case 0x33: p->fl = 0xFF; break;
    case 0x34: p->fl |= 1; break;
    case 0x36: p->fl |= 2; break;
    case 0x35: p->fl |= 4; break;
    }
}
