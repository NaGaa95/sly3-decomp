// SLY3_CFLAGS: -Os -G0
struct InputState { float leftX, leftY, leftAmount, rightX, rightY, rightAmount; unsigned int held18; float leftTimes[2], rightTimes[2]; void *vtable2C; };
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
void func_001A9960(struct InputState *input, float amount)
{
    float now;
    input->leftAmount = amount;
    now = D_0036BB98.now;
    input->leftTimes[amount > 0.0f] = now;
}
