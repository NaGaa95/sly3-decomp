// SLY3_CFLAGS: -Os -G0
struct CounterWord { char unknown_0[0xC]; int count; };
int func_00259D50(struct CounterWord *counter)
{
    return --counter->count;
}
