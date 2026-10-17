// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct SpawnTask { unsigned char prefix[0x1C]; void *link; qword value; };
struct SpawnSelf {
    unsigned char prefix[4]; void *owner; unsigned char gap8[4]; void *first; void *second; unsigned char gap14[4]; int mode;
    unsigned char gap1C[0x130 - 0x1C]; struct SpawnTask *firstTask; struct SpawnTask *secondTask; int identifier;
    unsigned char gap13C[0x140 - 0x13C]; qword firstValue; qword secondValue;
};
struct SpawnTask *func_0012FFB0(int kind, void *owner, void *channel, int mode, int identifier);
qword func_0028B388(void *a, void *b);
void func_0028ECE0(void *owner, void *channel, void *task);
void func_0014BC70(struct SpawnSelf *self)
{
    if(self->first) {
        if(!self->firstTask) {
            self->firstTask = func_0012FFB0(0xA, self->owner, self->first, 0, self->identifier);
            self->firstTask->link = self;
            self->firstValue = func_0028B388(self->first, self->first);
            self->firstTask->value = self->firstValue;
            func_0028ECE0(self->owner, self->first, self->firstTask);
        }
    }
    if(self->second) {
        if(!self->secondTask) {
            if(self->mode >= 2) {
                self->secondTask = func_0012FFB0(0xA, self->owner, self->second, 0, self->identifier);
                self->secondTask->link = self;
                self->secondValue = func_0028B388(self->second, self->second);
                self->secondTask->value = self->secondValue;
                func_0028ECE0(self->owner, self->second, self->secondTask);
            }
        }
    }
}
