// Reference: Sly 2 src/lib/func_002342D0.c; target Sly 3 0x00292F50.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_00293238(int);

int func_00292F50(const char *a, const char *b)
{
    while (*a && func_00293238(*a) == func_00293238(*b)) {
        a++;
        b++;
    }
    return func_00293238(*(unsigned char *)a) - func_00293238(*(unsigned char *)b);
}
