// Sly 2 counterpart: StartThread_2355E0 (decomp src/lib/StartThread_2355E0.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
// MATCH: thread-context reset is one noreorder asm block (keeps GNU as from filling the EI jal slot).
typedef struct {
    int status; void *entry; char *stack; int stackSize;
    void *gpReg; int initPriority; int currentPriority; unsigned attr;
    unsigned option; int waitType; int waitId; int wakeupCount;
} ThreadParam;
int func_00293D80(void);
int func_002980D0(void);
int func_00298120(void);
int func_002935A0(int tid, ThreadParam *info);
int func_002934C0(int tid, void *arg);
int func_00294260(int tid, void *arg)
{
    ThreadParam info;
    int r;
    char *p;

    if (func_00293D80() != 0)
        return -1;
    if (func_002980D0() == 0)
        return -1;
    r = func_002935A0(tid, &info);
    if (r < 0) {
        func_00298120();
        return r;
    }
    if (info.status == 0x10) {
    p = info.stack + info.stackSize - 0x2A0;
    __asm__ __volatile__(
        ".set noreorder\n\tsq $0, 0x0(%0)\n\tsq $0, 0x10(%0)\n\tsq $0, 0x20(%0)\n\tsq $0, 0x30(%0)\n\t"
        "sq $0, 0x40(%0)\n\tsq $0, 0x50(%0)\n\tsq $0, 0x60(%0)\n\tsq $0, 0x70(%0)\n\t"
        "sq $0, 0x80(%0)\n\tsq $0, 0x90(%0)\n\tsq $0, 0xA0(%0)\n\tsq $0, 0xB0(%0)\n\t"
        "sq $0, 0xC0(%0)\n\tsq $0, 0xD0(%0)\n\tsq $0, 0xE0(%0)\n\tsq $0, 0xF0(%0)\n\t"
        "sq $0, 0x100(%0)\n\tsq $0, 0x110(%0)\n\tsq $0, 0x120(%0)\n\tsq $0, 0x130(%0)\n\t"
        "sq $0, 0x140(%0)\n\tsq $0, 0x150(%0)\n\tsq $0, 0x160(%0)\n\tsq $0, 0x170(%0)\n\t"
        "sq $0, 0x180(%0)\n\tsq $0, 0x190(%0)\n\tsq $0, 0x1A0(%0)\n\tsq $0, 0x1B0(%0)\n\t"
        "sq $0, 0x200(%0)\n\tsq $0, 0x210(%0)\n\tsq $0, 0x220(%0)\n\tsq $0, 0x230(%0)\n\t"
        "sq $0, 0x240(%0)\n\tsq $0, 0x250(%0)\n\tsq $0, 0x260(%0)\n\tsq $0, 0x270(%0)\n\t"
        "sll $8, %1, 0\n\tsd $8, 0x40(%0)\n\t"
        "lw $8, 0x1C0(%0)\n\tsd $8, 0x1C0(%0)\n\tsd $0, 0x1C8(%0)\n\t"
        "lw $8, 0x1D0(%0)\n\tsd $8, 0x1D0(%0)\n\tsd $0, 0x1D8(%0)\n\t"
        "lw $8, 0x1E0(%0)\n\tsd $8, 0x1E0(%0)\n\tsd $0, 0x1E8(%0)\n\t"
        "lw $8, 0x1F0(%0)\n\tsd $8, 0x1F0(%0)\n\tsd $0, 0x1F8(%0)\n\t.set reorder"
        : : "r"(p), "r"(arg) : "$8", "memory");
    func_00298120();
    return func_002934C0(tid, arg);
    }
    func_00298120();
    return -1;
}
