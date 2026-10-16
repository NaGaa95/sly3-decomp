// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct TargetView {
    unsigned char opaque0[0x18F0];
    void *owner;
    unsigned char opaque18F4[0x19A0 - 0x18F4];
    int first;
    int second;
    unsigned char opaque19A8[0x19D0 - 0x19A8];
    Quad value;
    unsigned char opaque19E0[0x1A1C - 0x19E0];
    int active;
    int cleared;
    float scale;
};
extern void *D_00370AC0;
void func_001DE690(void *actor, int state);
void func_001E2388(void *receiver, int first, int second, Quad value, float scale)
{
    struct TargetView *view = (struct TargetView *)receiver;
    view->first = first;
    view->second = second;
    view->owner = D_00370AC0;
    func_001DE690(receiver, 0x10);
    view->value = value;
    view->scale = scale;
    view->active = 1;
    view->cleared = 0;
}
