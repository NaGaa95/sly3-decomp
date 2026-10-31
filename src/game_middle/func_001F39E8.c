// Set the "no value" flag at +0x1A0 from a boolean-negated argument.
// SLY3_CFLAGS: -O2 -G0 -ffast-math

struct FlagHolder {
    char pad[0x1A0];
    int isZero;
};

void func_001F39E8(struct FlagHolder *self, int value)
{
    self->isZero = value == 0;
}
