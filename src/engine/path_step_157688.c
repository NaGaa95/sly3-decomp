// SLY3_CFLAGS: -Os -G0

typedef int Qword __attribute__((mode(TI)));
struct StepPath { unsigned char prefix[0xD4]; int fixed; };
struct StepSelf {
    unsigned char prefix[0x18]; void *view; unsigned char gap1C[0x30 - 0x1C]; struct StepPath *path; int reverse; float value; unsigned char gap3C[4]; Qword point;
};
float func_0022DFB0(struct StepPath *path);
float func_0022DFD8(struct StepPath *path);
float func_0022E058(float parameter);
void func_0022E330(struct StepPath *path, void *point, void *direction, float parameter);
void func_00157A80(void *view, int changed);
void func_00157970(void *view, Qword point);
void func_00157688(struct StepSelf *self, int force)
{
    float step = 200.0f;
    float target;
    int changed;
    if(!self->reverse) step = -step;
    changed = 0;
    target = self->value + step;
    if(!self->path->fixed) {
        float low = func_0022DFB0(self->path);
        float high = func_0022DFD8(self->path);
        float clamped;
        if(target < low) clamped = low;
        else if(high < target) clamped = high;
        else clamped = target;
        if(clamped != target) {
            target = clamped;
            changed = 1;
        }
    } else {
        target = func_0022E058(target);
    }
    if(!force) {
        if(__builtin_fabsf(self->value - target) < 5.0f) return;
    }
    self->value = target;
    func_0022E330(self->path, &self->point, 0, target);
    {
        void *view = self->view;
        func_00157A80(view, changed);
        func_00157970(view, self->point);
    }
}
