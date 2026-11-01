// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } VectorWord;
struct Method { short delta, reserved; void (*function)(void *); };
struct Table { unsigned char prefix[0x370]; struct Method method; };
struct Target { unsigned char prefix[0x1C]; float scale; };
struct Mover { unsigned char prefix[8]; float speed; };
struct Self {
    unsigned char prefix0[0xC];
    struct Table *table;
    unsigned char gap10[0x2F - 0x10];
    unsigned long flags : 8;
    unsigned char gap30[0x134 - 0x30];
    struct Mover *mover;
    unsigned char gap138[0x1A0 - 0x138];
    qword direction;
    unsigned char gap1B0[0x110C - 0x1B0];
    float timeScale;
    unsigned char gap1110[0x1470 - 0x1110];
    unsigned int mode;
};
void func_00152A48(void *);
void func_001E9678(void *);
void func_001E9798(void *);
void func_001EA750(void *);
void func_001E96E8(void *);
void func_0024E878(void *, float);
void func_00258CF0(void *, float);
void func_00258DA0(void *);
void func_001B9C48(void *);
void func_001B30E8(void *);
void func_001C2B48(void *);
struct Target *func_00156AB0(void *);
qword func_0024F278(void *, struct Target *, float);
static inline qword ScaleX(qword vector, float scale)
{
    VectorWord s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(scale));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(vector), "j"(s.q));
    return r;
}
#define Base(self, off) ((void *)((char *)(self) + (off)))
void func_001E9500(struct Self *self)
{
    func_00152A48(self);
    if (self->flags & 1) {
        func_001E9678(self);
        func_001E9798(self);
        func_001EA750(self);
        switch (self->mode) {
        case 0: {
            struct Method *method = &self->table->method;
            method->function((char *)self + method->delta);
            break;
        }
        case 1:
            func_0024E878(self, self->timeScale);
            func_00258CF0(Base(self, 0x1480), 1.0f);
            func_00258DA0(Base(self, 0x1480));
            break;
        case 2:
            func_0024E878(self, self->timeScale);
            func_00258CF0(Base(self, 0x1530), self->mover->speed);
            func_00258DA0(Base(self, 0x1530));
            break;
        case 3:
            func_0024E878(self, self->timeScale);
            func_00258CF0(Base(self, 0x15E0), self->mover->speed);
            func_00258DA0(Base(self, 0x15E0));
            break;
        case 4:
            func_001B9C48(Base(self, 0x320));
            break;
        case 5:
            func_001B30E8(Base(self, 0x500));
            break;
        case 6:
            func_001C2B48(Base(self, 0xE40));
            break;
        case 8: {
            struct Target *target = func_00156AB0(self);
            self->direction = ScaleX(func_0024F278(self, target, target->scale), -1.0f);
            break;
        }
        }
        func_001E96E8(self);
    }
}
