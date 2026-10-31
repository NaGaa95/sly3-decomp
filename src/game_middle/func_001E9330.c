// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#define Word(p, o) (*(int *)((char *)(p) + (o)))
#define Float(p, o) (*(float *)((char *)(p) + (o)))

struct S { int a; char pad[0x8C]; int b; float g, h; };
void func_00152218(void *);
void func_00258930(struct S *, int, int);
extern void *D_0038AE94;

void func_001E9330(void *p)
{
    void *block;
    func_00152218(p);
    Word(p, 0x1470) = -1;
    Word(p, 0x1114) = 0x94;
    func_00258930((struct S *)((char *)p + 0x1480), (int)p, 0x94);
    func_00258930((struct S *)((char *)p + 0x1530), (int)p, Word(p, 0x1114));
    func_00258930((struct S *)((char *)p + 0x15E0), (int)p, Word(p, 0x1114));
    {
        float start = 125.0f, minimum = -100.0f, maximum = 100.0f, width = 50.0f,
              base = -10.0f, limit = 250.0f, second = 1.0f, third = 4500.0f;
        block = (char *)p + 0x1180;
        Float(p, 0x1158) = start;
        Float(p, 0x1170) = minimum;
        Float(p, 0x1174) = maximum;
        Float(p, 0x1178) = width;
        Float(p, 0x117C) = base;
        Float(p, 0x1180) = limit;
        Float(block, 0xC) = third;
        Float(block, 0x8) = second;
        Word(block, 0x4) = 0;
    }
    Word(p, 0x164) = 0x10;
    Word(p, 0x1110) = 0x2080;
    Word(p, 0x16A8) = -1;
    Word(p, 0x16E8) = 4;
    Float(p, 0x16F0) = 0.5f;
    D_0038AE94 = p;
}
