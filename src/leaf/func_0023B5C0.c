// SLY3_CFLAGS: -Os -G0
// Accessors for packed 64-bit flag words of an object: a signed 4-bit field at bits 52..55 of the word at +0x120 (set/get)
// and flag bit 34 of the word at +0xC0 (get; the setter is func_0023B620).
struct Object {
    char unknown0[0xC0];
    unsigned long low34 : 34; unsigned long flag34 : 1; unsigned long high29 : 29;
    char unknownC8[0x120 - 0xC8];
    long low52 : 52; long field52 : 4; long high8 : 8;
};

void func_0023B5C0(struct Object *p, unsigned int value)
{
    p->field52 = value;
}

int func_0023B5F8(struct Object *p)
{
    return p->field52;
}

unsigned long func_0023B610(struct Object *p)
{
    return p->flag34;
}
