// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#define Word(p, o) (*(int *)((char *)(p) + (o)))
#define Float(p, o) (*(float *)((char *)(p) + (o)))

struct S { int a; char pad[0x8C]; int b; float g, h; };
void func_00152218(void *);
void func_00258930(struct S *, int, int);
void func_00271E38(void *, void *);
extern void *D_0038AE90;

void func_001DCA30(void *p)
{
    void *block;
    float width = 50.0f;
    func_00152218(p);
    Float(p, 0x230) = width;
    Word(p, 0x1114) = 0x15;
    Word(p, 0x1528) = -1;
    Word(p, 0x1890) = -1;
    Word(p, 0x18C0) = -1;
    Word(p, 0x1520) = -1;
    Word(p, 0x1588) = -1;
    Word(p, 0x158C) = -1;
    Word(p, 0x1594) = -1;
    Word(p, 0x1874) = -1;
    Word(p, 0x1AD4) = -1;
    Word(p, 0x1C64) = -1;
    Float(p, 0x1560) = 1500.0f;
    Float(p, 0x1564) = 3500.0f;
    Float(p, 0x1148) = 60.0f;
    Float(p, 0x1158) = 125.0f;
    func_00258930((struct S *)((char *)p + 0x1470), (int)p, 0x15);
    func_00258930((struct S *)((char *)p + 0x15A0), (int)p, Word(p, 0x1114));
    func_00258930((struct S *)((char *)p + 0x1680), (int)p, Word(p, 0x1114));
    {
        float second = 1.0f, third = 4500.0f;
        block = (char *)p + 0x1180;
        Float(p, 0x1570) = -60.0f;
        Float(p, 0x1170) = -100.0f;
        Float(p, 0x1174) = 100.0f;
        Float(p, 0x1178) = width;
        Float(p, 0x117C) = -10.0f;
        Float(p, 0x1180) = 250.0f;
        Float(block, 0xC) = third;
        Float(block, 0x8) = second;
        Word(block, 0x4) = 0;
    }
    func_00271E38((char *)p + 0x18E0, p);
    Word(p, 0x164) = 4;
    Word(p, 0x1110) = 0x21F8;
    D_0038AE90 = p;
}
