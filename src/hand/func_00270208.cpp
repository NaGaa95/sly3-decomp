// Sly 2 reference: src/hand/CchAchFromUl__FPciUlUi.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" char D_00349D70[];
extern "C" void *func_001D2898(void *dst, const void *src, int cb) __asm__("func_001D2898");
int CchAchFromUl(char *ach, int cch, unsigned long ul, unsigned int radix) __asm__("func_00270208");
int CchAchFromUl(char *ach, int cch, unsigned long ul, unsigned int radix)
{
    char *pchEnd = ach + cch;
    char *pch = pchEnd;
    do {
        *--pch = D_00349D70[(int)(ul % radix)];
        ul /= radix;
    } while (ul != 0 && pch >= ach);
    int c = pchEnd - pch;
    if (c != 0 && ach < pch)
        func_001D2898(ach, pch, c);
    return c;
}
