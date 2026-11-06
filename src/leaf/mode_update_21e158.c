// Per-frame mode update of the controller: advance the state machine (idle, cancel, ramp up, ramp down, pick-up) until the mode stops changing, easing the two ramp values towards their targets.
// SLY3_CFLAGS: -Os -G0
struct Target { unsigned char pad00[0x11A0]; int pickup; unsigned char pad11A4[0x11C4 - 0x11A4]; int kind; };
struct Object {
    unsigned char opaque00[0x48];
    int group;
    unsigned char opaque4C[0x120 - 0x4C];
    float current0;
    float target0;
    float current1;
    float target1;
    unsigned char opaque130[8];
    int mode;
    struct Target *target;
};
struct Ramp { float rate[4]; };
extern struct Ramp D_00349020, D_00349030;
extern float D_0036BB9C;
void func_0021DF20(struct Object *self, int mode);
int func_0013B500(void *object, int id);
int func_00260758(struct Object *self, int id);
void func_00261580(struct Object *self, int id, float value);
float func_0011E598(struct Ramp *ramp, int a, float current, float target, float step);
void func_0021E158(struct Object *self)
{
    int mode;
    do {
        mode = self->mode;
        switch (mode) {
        case -1:
            break;
        case 0:
            if (self->group - 2U < 2)
                func_0021DF20(self, 1);
            break;
        case 1:
        case 5:
        case 6:
            if (self->target0 <= 0.0f) {
                func_0021DF20(self, -1);
                break;
            }
            if (self->target0 < self->current0) {
                func_0021DF20(self, 2);
                break;
            }
            if (self->current0 < self->target0) {
                func_0021DF20(self, 3);
                break;
            }
            if (self->target1 != self->current1) {
                func_0021DF20(self, 4);
                break;
            }
            if (func_0013B500(self->target, 0x33)) {
                if (self->target->kind == 4) {
                    func_0021DF20(self, 6);
                    break;
                }
                if (self->target->pickup != -1) {
                    func_0021DF20(self, 5);
                    break;
                }
            }
            func_0021DF20(self, 1);
            break;
        case 2:
            if (func_00260758(self, 0x3C4)) break;
            func_0021DF20(self, 3);
            break;
        case 3:
            if (self->current0 < self->target0)
                self->current0 = self->target0;
            else
                self->current0 = func_0011E598(&D_00349020, 0, self->current0, self->target0, D_0036BB9C);
            func_00261580(self, 0x3CA, self->current0);
            if (self->current0 == self->target0)
                func_0021DF20(self, 1);
            break;
        case 4:
            if (self->current1 < self->target1)
                self->current1 = self->target1;
            else
                self->current1 = func_0011E598(&D_00349030, 0, self->current1, self->target1, D_0036BB9C);
            func_00261580(self, 0x3CB, self->current1);
            if (self->current1 == self->target1)
                func_0021DF20(self, 1);
            break;
        }
    } while (self->mode != mode);
}
