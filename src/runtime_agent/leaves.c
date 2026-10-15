// SLY3_CFLAGS: -O2 -G0
extern void func_0028FFD8(void *object);
extern void func_001C7CC8(void *object);

void *func_002900D0(void *object)
{
    func_0028FFD8(object);
    return (char *)object + 144;
}

void func_00290400(void *object)
{
    int *state = (int *)object;
    func_001C7CC8(object);
    if (state[17] != -1)
        state[17] = -1;
}

// Original integer ratio conversion keeps runtime multiply/divide.
// Empty register constraints preserve the original operand lifetimes;
// all arithmetic and control remain compiler-generated.
int func_00291DD0(int input)
{
    register int multiplier __asm__("$2") = 1524;
    register int divisor __asm__("$3") = 741;
    __asm__("" : "+r"(multiplier), "+r"(divisor));
    return (input * multiplier) / divisor;
}
