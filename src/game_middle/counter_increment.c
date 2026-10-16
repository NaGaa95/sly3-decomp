// SLY3_CFLAGS: -Os -G0
struct CounterView { unsigned char opaque[0x44F8]; int count; };

void func_001C5250(void *receiver)
{
    struct CounterView *view = (struct CounterView *)receiver;
    view->count++;
}
