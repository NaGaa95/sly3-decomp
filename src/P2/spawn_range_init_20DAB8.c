// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct SpawnRange {
    unsigned char prefix0[0x20];
    float low[3];
    float gap2C;
    float high[3];
    unsigned char gap3C[0x50 - 0x3C];
    qword q50;
};
struct SpawnSelf {
    unsigned char prefix0[0x18];
    float x18;
    unsigned char gap1C[4];
    qword q20;
    qword q30;
    unsigned char gap40[0x90 - 0x40];
    float vector90[3];
    unsigned char gap9C[0xF0 - 0x9C];
    struct SpawnRange *range;
    unsigned char gapF4[0x100 - 0xF4];
    qword q100;
};
extern char D_00475480[];
extern qword D_00341FE0;
void *func_00165B28(void *context);
void func_0020BC20(struct SpawnSelf *self, qword value, float weight);
qword func_001678C8(void *context, qword value);
float func_0011E940(float low, float high);
void func_0020DAB8(struct SpawnSelf *self, qword value, float weight)
{
    void *context = func_00165B28(D_00475480);
    float x, y, z;
    func_0020BC20(self, value, weight);
    self->q100 = func_001678C8(context, value);
    x = func_0011E940(self->range->low[0], self->range->high[0]);
    y = func_0011E940(self->range->low[1], self->range->high[1]);
    z = func_0011E940(self->range->low[2], self->range->high[2]);
    {
        float *vector = self->vector90;
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }
    self->x18 = 0.5f;
    self->q30 = D_00341FE0;
    self->q20 = self->range->q50;
}
