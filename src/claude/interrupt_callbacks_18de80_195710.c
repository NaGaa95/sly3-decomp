// SLY3_CFLAGS: -Os -G0
// Scratchpad color conversion completion and GS interrupt callbacks.
void func_0018DD60(void *);
void func_00293950(int);
int func_002936D0(int);
extern int D_0036E694, D_0036E698;

static inline void FinishInterrupt(void)
{
    __asm__ volatile("sync\n\tei" : : : "memory");
}

int func_0018DE80(void)
{
    func_0018DD60((void *)0x1100C340);
    func_00293950(0);
    *(volatile unsigned int *)0x10003C10 = 8;
    FinishInterrupt();
    return -1;
}

int func_00195710(void)
{
    if (D_0036E698 && (*(volatile unsigned long *)0x12001000 & 2)) {
        D_0036E698 = 0;
        func_002936D0(D_0036E694);
    }
    FinishInterrupt();
    return -1;
}
