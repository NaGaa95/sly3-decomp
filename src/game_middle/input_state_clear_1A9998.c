// SLY3_CFLAGS: -Os -G0
struct InputState {
    float leftX, leftY, leftAmount, rightX, rightY, rightAmount;
    unsigned int held18;
    float leftTimes[2], rightTimes[2];
    void *vtable2C;
    unsigned int pending30;
};
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
void func_001A9998(struct InputState *input)
{
    float now, zero = 0.0f;
    input->pending30 = 0;
    input->leftAmount = zero;
    input->leftY = zero;
    input->leftX = zero;
    input->rightAmount = zero;
    input->rightY = zero;
    input->rightX = zero;
    input->held18 = 0;
    now = D_0036BB98.now;
    input->rightTimes[0] = now;
    input->leftTimes[0] = now;
}
