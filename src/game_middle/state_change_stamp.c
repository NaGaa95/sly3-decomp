// SLY3_CFLAGS: -Os -G0
struct StateOwner { unsigned char opaque[0x148]; int token; };
struct StateView {
    struct StateOwner *owner;
    unsigned char opaque04[0x2C];
    int state;
    float stamp;
    int mode;
    unsigned char opaque3C[0x14];
    int counter;
    unsigned char opaque54[0x14];
    int token;
};
extern float D_0036BB98;
void func_001B5830(void *receiver, int state)
{
    struct StateView *view = (struct StateView *)receiver;
    if (state != view->state) {
        view->state = state;
        view->stamp = D_0036BB98;
        view->counter = 0;
        if (state > 0) {
            if (state >= 3) {
                if (state == 3)
                    view->mode = 1;
            } else {
                if (view->owner->token == view->token)
                    view->mode = 2;
                else
                    view->mode = 0;
            }
        }
    }
}
