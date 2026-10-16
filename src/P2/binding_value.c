// SLY3_CFLAGS: -Os -G0
struct LinkedValue { char unknown_0[0x10]; int value; };
struct LinkedRecord { char unknown_0[8]; struct LinkedValue *linked; };
int func_00267960(struct LinkedRecord *record)
{
    return record->linked->value;
}
