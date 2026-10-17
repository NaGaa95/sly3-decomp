// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct LimitMethod { short adjustment, word2; void *function; };
struct LimitTable { unsigned char prefix[0x110]; struct LimitMethod methods[3]; };
struct LimitSelf {
    unsigned char prefix0[0xC];
    struct LimitTable *table;
    unsigned char gap10[0xC70 - 0x10];
    unsigned char anchor[0x30];
    qword saved;
    float distance;
};
extern qword D_00317560;
extern qword D_00325880;
extern void *D_00479A64;
void func_0023D938(void *self, qword value);
void func_0023D9D0(void *self, qword value);
float func_001B83F0(float a, float b, float c, float d, qword delta, qword axis);
void *func_001F4A80(void *receiver);
void func_00166548(char *pose);
void func_0017D840(void *table, void *actor);
void func_002075E8(void *self, int mode);
static inline qword LimitSub(qword first, qword second)
{
    qword result;
    asm("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(first), "j"(second));
    return result;
}
void func_00204CB0(struct LimitSelf *self, float a, float b, float c, float d, float limit)
{
    struct LimitMethod *method;
    unsigned char *anchor = self->anchor;
    qword saved;
    float distance;
    func_0023D938(self, D_00317560);
    func_0023D9D0(self, D_00317560);
    saved = self->saved;
    method = &self->table->methods[2];
    distance = func_001B83F0(a, b, c, d,
        LimitSub(saved, *(qword *)((char *)((void *(*)(void *))method->function)((char *)self + method->adjustment) + 0x30)),
        D_00325880);
    if (limit < distance) {
        method = &self->table->methods[0];
        ((void (*)(void *, qword))method->function)((char *)self + method->adjustment, self->saved);
        method = &self->table->methods[1];
        ((void (*)(void *, void *))method->function)((char *)self + method->adjustment, anchor);
        func_00166548((char *)func_001F4A80(self));
        func_0017D840(D_00479A64, self);
    } else {
        self->distance = distance;
        func_002075E8(self, 4);
    }
}
