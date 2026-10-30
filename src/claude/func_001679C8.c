// SLY3_CFLAGS: -Os -G0
struct S1 { char pad[0x14]; float g; };
struct S0 { char pad[0x11C]; float g; char pad2[0x300-0x120]; struct S1 *p; };
void func_001679C8(struct S0 *p, float g)
{
    p->g = g;
    if (p->p) p->p->g = g;
}
