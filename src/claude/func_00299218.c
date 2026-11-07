// Sly 2 counterpart: func_0023A598 (decomp src/lib/func_0023A598.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
unsigned long func_00299218(unsigned int sec, unsigned int usec)
{
    return (unsigned long)sec * 147456000 + (unsigned long)usec * 147456000 / 1000000;
}
