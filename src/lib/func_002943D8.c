// Reference: Sly 2 src/lib/_DelayThreadHandler.c; target Sly 3 0x002943D8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
void func_002936D0(int sema);
int _DelayThreadHandler(int id, unsigned short t, int a2, int sema)
{
    func_002936D0(sema);
    __asm__ volatile("sync");
    __asm__ volatile("ei");
    return 0;
}
