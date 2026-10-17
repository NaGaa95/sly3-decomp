// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
inline float PackedVectorZ(qword vector) {
    float scalar;
    asm("pextuw %0,$0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}
struct PollEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct PollSelf {
    unsigned char prefix[0xC]; struct PollEntry *table; unsigned char gap10[0x2E4 - 0x10]; void *effect;
    unsigned char gap2E8[0x2F4 - 0x2E8]; int state; float stamp;
};
extern "C" {
extern float D_0036BB98;
extern float D_0047A2B0;
int func_001468A8(void *self);
void func_00143B30(void *self, int state);
int func_00138AC8(void *effect);
void func_00142AE0(void *self, int mode);
}

extern "C" void func_00143D08(PollSelf *self)
{
    int previous;
    do {
        previous = self->state;
        switch(previous) {
        case -1:
            break;
        case 0:
            if(D_0036BB98 - self->stamp > 0.5f || func_001468A8(self)) func_00143B30(self, 1);
            break;
        case 1:
            if(self->effect) {
                if(func_00138AC8(self->effect)) func_00143B30(self, 2);
            } else if(D_0036BB98 - self->stamp > 1.0f) {
                func_00143B30(self, 2);
            }
            break;
        case 2: {
            qword position = *(qword *)(self->table[36].method((unsigned char *)self + self->table[36].delta) + 0x30);
            int below = PackedVectorZ(position) < D_0047A2B0;
            if(below) func_00142AE0(self, 1);
            break;
        }
        }
    } while(previous != self->state);
}
