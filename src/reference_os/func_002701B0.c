// Sly 2 reference: src/hand/UnRadixFromChConversion__Fc.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
int func_002701B0(unsigned char ch)
{
    switch (ch) {
    case 'd':
    case 'i':
    case 'u':
        return 10;
    case 'B':
    case 'b':
        return 2;
    case 'o':
        return 8;
    case 'x':
        return 16;
    default:
        return 10;
    }
}
