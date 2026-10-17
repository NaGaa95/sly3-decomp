// SLY3_CFLAGS: -Os -G0
#define Word(p, o) (*(int *)((char *)(p) + (o)))
#define Float(p, o) (*(float *)((char *)(p) + (o)))
void func_00152218(void *);
void func_00258930(void *, int, int);
extern void *D_0036B250;

void func_0013D2D0(void *p)
{
    void *block;
    func_00152218(p);
    Word(p, 0x114C) = 0;
    Word(p, 0x1520) = -1;
    Word(p, 0x1820) = -1;
    Word(p, 0x18F0) = -1;
    Word(p, 0x1924) = -1;
    Float(p, 0x1148) = 45.0f;
    Float(p, 0x1158) = 125.0f;
    Word(p, 0x1114) = 0x73;
    func_00258930((char *)p + 0x1470, (int)p, 0x73);
    func_00258930((char *)p + 0x1770, (int)p, Word(p, 0x1114));
    {
        float minimum = -100.0f, maximum = 100.0f, width = 50.0f, base = -10.0f, limit = 250.0f, second = 1.0f, third = 4500.0f;
        block = (char *)p + 0x1180;
        Float(p, 0x1170) = minimum;
        Float(p, 0x1174) = maximum;
        Float(p, 0x1178) = width;
        Float(p, 0x117C) = base;
        Float(p, 0x1180) = limit;
        Float(block, 0xC) = third;
        Float(block, 0x8) = second;
        Word(block, 0x4) = 0;
    }
    Word(p, 0x164) = 2;
    Word(p, 0x1110) = 0x2880;
    Word(p, 0x195C) = 6;
    Word(p, 0x1968) = 0xA;
    Word(p, 0x1974) = 0x10;
    Word(p, 0x1980) = 0xD;
    Word(p, 0x198C) = 0xF;
    Word(p, 0x1998) = 8;
    Word(p, 0x1950) = 4;
    Word(p, 0x19A8) = 4;
    D_0036B250 = p;
}
