// Reference: Sly 2 src/lib/func_002394A0.c; target Sly 3 0x00298120.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_00298120(void)
{
    int status;
    __asm__ volatile("mfc0 %0, $12" : "=r"(status));
    status &= 0x10000;
    __asm__ volatile("ei");
    return status != 0;
}
