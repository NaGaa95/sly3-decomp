// SLY3_CFLAGS: -Os -G0 -ffast-math
typedef int qword __attribute__((mode(TI)));
struct BlendPair { qword first; qword second; };
struct BlendClock { float time; float step; };
struct BlendSelf {
    unsigned char prefix0[0x14];
    float start, length;
    unsigned char gap1C[0x70 - 0x1C];
    qword q70;
    qword q80;
    qword q90;
    unsigned char gapA0[0xF0 - 0xA0];
    struct BlendPair *pair;
    unsigned char gapF4[0x100 - 0xF4];
    qword q100;
};
extern char D_00475480[];
extern struct BlendClock D_0036BB98;
void *func_00165B28(void *context);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, int);
qword func_00167838(void *p, qword q);
void func_0020DBA0(struct BlendSelf *self)
{
    void *context = func_00165B28(D_00475480);
    float delay = self->start + self->length - D_0036BB98.time;
    delay = D_0036BB98.step > delay ? D_0036BB98.step : delay;
    func_00118558(delay, D_0036BB98.step, 1.0f, self->q100, self->q90, self->pair->first, self->pair->second, &self->q100, &self->q90, 0);
    self->q80 = self->q70;
    self->q70 = func_00167838(context, self->q100);
}
