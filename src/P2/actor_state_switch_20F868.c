// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct StateMethod { short adjustment, word2; void *function; };
struct StateTable { unsigned char prefix[0x120]; struct StateMethod query; };
struct StateChannel { unsigned char prefix[0x30]; qword value; };
struct StateSelf {
    unsigned char prefix0[0xC];
    struct StateTable *methods;
    unsigned char gap10[0x48 - 0x10];
    struct StateChannel *channelA;
    struct StateChannel *channelB;
    struct StateChannel *channelC;
    unsigned char gap54[0x1CC - 0x54];
    int state;
    void *taskA;
    void *taskB;
    unsigned char gap1D8[0x204 - 0x1D8];
    float heading;
};
extern unsigned char D_0036C700[];
void func_0028F068(void *receiver, void *channel, int mode);
void func_0023EC98(void *receiver, int mode);
void func_00240DB0(void *owner);
void func_001309D8(void *task);
void *func_00130078(void *owner, void *channel, int a, int b, int c, qword value);
qword func_0011D3C0(void *matrix);
float func_002A3EE8(float y, float x);
void func_001854C8(void *context, int event, void *owner);
void func_0020F868(struct StateSelf *self, int state)
{
    struct StateMethod *method;
    float *vector;
    if (state == self->state)
        return;
    switch (self->state) {
    case 2:
        func_0028F068(self, self->channelA, 1);
        func_0028F068(self, self->channelC, 1);
        func_0023EC98(self, 0);
        break;
    case 1:
        func_001309D8(&self->taskA);
        func_001309D8(&self->taskB);
        break;
    case 3:
        func_00240DB0(self);
        break;
    }
    self->state = state;
    switch (state) {
    case 1:
        self->taskA = func_00130078(self, self->channelA, 1, 0x13, 2, self->channelA->value);
        self->taskB = func_00130078(self, self->channelB, 1, 0x13, 2, func_0011D3C0(self->channelB));
        break;
    case 2:
        func_0028F068(self, self->channelA, 2);
        func_0028F068(self, self->channelC, 2);
        func_0023EC98(self, 4);
        method = &self->methods->query;
        vector = (float *)((void *(*)(void *))method->function)((char *)self + method->adjustment);
        self->heading = func_002A3EE8(vector[1], vector[0]);
        break;
    case 3:
        func_001854C8(D_0036C700, 12, self);
        break;
    }
}
