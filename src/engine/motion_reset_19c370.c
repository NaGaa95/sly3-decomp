// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword r[3]; } M3;
struct MotionSelf {
    unsigned char prefix[0x1F0]; int state;
    unsigned char gap1F4[0x268 - 0x1F4]; float angle; unsigned char gap26C[4];
    Qword target; int flag;
};
extern Qword D_00317550;
extern Qword D_00317560;
extern M3 D_00321F80;
extern unsigned char D_00321F90[], D_00321FA0[];
void func_00243738(void *self);
void func_0019F6D8(void *self);
M3 *func_0011C8C0(M3 *matrix, float angle, Qword axis);
void func_0023EDE8(void *self, M3 matrix, M3 *limits);
void func_00244828(void *self, Qword correction);
void func_0023F180(void *self, Qword first, int second, Qword third, void *table);
void func_0019C370(struct MotionSelf *self)
{
    M3 copy;
    M3 matrix;
    int state = self->state;
    if(state == 5) {
        func_00243738(self);
        return;
    }
    if(state != 2) {
        if(state >= 2) {
            if(state < 5) return;
        }
        func_0019F6D8(self);
    }
    func_0011C8C0(&matrix, self->angle, D_00317550);
    copy = matrix;
    func_0023EDE8(self, copy, &D_00321F80);
    if(self->flag) {
        func_00244828(self, self->target);
        func_0023F180(self, D_00317560, 0, D_00317560, D_00321F90);
    } else {
        func_0023F180(self, D_00317560, 0, self->target, D_00321FA0);
    }
}
