// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct EffectSelf { unsigned char prefix[0x288]; int identifier; };
extern qword D_00317560;
int func_002533C0(void *self, int index);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);
void func_001F60E8(struct EffectSelf *self)
{
    if (func_002533C0(self, 0x41))
        func_00240CB0(self, self->identifier, self, 0x200, 10, 0, D_00317560, D_00317560, 0);
}
