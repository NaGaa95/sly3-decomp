// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));

Quad *func_001EC6D8(Quad *cursor, Quad value)
{
    *++cursor = value;
    return cursor;
}
