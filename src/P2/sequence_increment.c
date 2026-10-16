// SLY3_CFLAGS: -Os -G0
struct SequenceCounter { char unknown_0[0x4C]; int sequence; };
int func_0028A470(struct SequenceCounter *counter)
{
    return ++counter->sequence;
}
