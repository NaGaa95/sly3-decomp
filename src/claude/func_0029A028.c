// Sly 2 counterpart: InitTLB32MB (decomp src/lib/InitTLB32MB.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned int PageMask, EntryHi, EntryLo0, EntryLo1; } TLBENT;
typedef struct {
    int nKernel, nDefault, nExtended, nWired;
    TLBENT *pKernel, *pDefault, *pExtended;
} TLBINFO;
extern TLBINFO D_0034BCB8;
extern char D_0032AD88[], D_0032ADC0[], D_0032ADD8[], D_0032ADF0[];
int func_00295660(const char *, ...);
void func_00298550(int);
void func_00299FD8(int, unsigned int, unsigned int, unsigned int, unsigned int);

int func_0029A028(void)
{
    register int i __asm__("$25"); /* the original keeps the TLB index in $t9 across calls */
    int n;
    int j;
    TLBENT *p;

    func_00295660(D_0032AD88, D_0034BCB8.nKernel - 1, D_0034BCB8.nKernel,
                  D_0034BCB8.nKernel + D_0034BCB8.nDefault - 1,
                  D_0034BCB8.nKernel + D_0034BCB8.nDefault,
                  D_0034BCB8.nKernel + D_0034BCB8.nDefault + D_0034BCB8.nExtended - 1);
    __asm__ __volatile__("mtc0 $0, $6\n\tsync.p");

    i = 0;
    n = D_0034BCB8.nKernel;
    if (n > 48) {
        func_00295660(D_0032ADC0);
        func_00298550(1);
    }
    p = D_0034BCB8.pKernel;
    for (; i < n; i++, p++)
        func_00299FD8(i, p->PageMask, p->EntryHi, p->EntryLo0, p->EntryLo1);

    n = i + D_0034BCB8.nDefault;
    if (n > 48) {
        func_00295660(D_0032ADD8);
        func_00298550(1);
    }
    p = D_0034BCB8.pDefault;
    for (; i < n; i++, p++)
        func_00299FD8(i, p->PageMask, p->EntryHi, p->EntryLo0, p->EntryLo1);

    D_0034BCB8.nWired = i;
    __asm__ __volatile__("mtc0 %0, $6\n\tsync.p" : : "r"(i));

    if (D_0034BCB8.nExtended > 0) {
        n = i + D_0034BCB8.nExtended;
        if (n > 48) {
            func_00295660(D_0032ADF0);
            func_00298550(1);
        }
        p = D_0034BCB8.pExtended;
        for (; i < n; i++, p++)
            func_00299FD8(i, p->PageMask, p->EntryHi, p->EntryLo0, p->EntryLo1);
    }
    for (j = i; j < 48; j++)
        func_00299FD8(j, 0, 0xE0000000 + (j << 13), 0, 0);
    return i;
}
