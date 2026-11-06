// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct PointDefaults {
    unsigned char prefix00[0x164];
    unsigned int color;
    unsigned char gap168[0x28];
    qword scale;
    qword noise;
    float amount, duration, distance, gain, rate, width;
    unsigned char gap1C8[4];
    int handle;
};
extern qword D_00325AF0, D_00325B00;
void func_001F3B50(void *receiver);
void func_001F43F8(void *receiver, int value);
int func_001F43F0(void *receiver);
void func_001F43D0(void *receiver, int value);
void func_0020ED28(struct PointDefaults *self)
{
    func_001F3B50(self);
    self->noise = D_00325AF0;
    self->duration = 3.0f;
    self->scale = D_00325B00;
    self->distance = 20.0f;
    self->gain = self->amount = 1.0f;
    self->rate = 6000.0f;
    self->width = 2.5f;
    func_001F43F8(self, 100);
    func_001F43D0(self, func_001F43F0(self));
    self->handle = -1;
    self->color = 0xFF;
}
