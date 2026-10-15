// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x10]; int x10; int x14; char p2[0x24]; int x3c; char p3[0x10]; int x50; };
void func_001A3018(struct S *p);
void func_001A2D80(struct S *p);
void func_001A3058(struct S *p)
{
    if (p->x3c >= 0) func_001A3018(p);
    else if (p->x50 >= 0) func_001A2D80(p);
    else {
        p->x10 = 0;
        p->x14 = 0;
    }
}
