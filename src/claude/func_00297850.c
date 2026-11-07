// Sly 2 counterpart: sceSifInitIopHeap (decomp src/lib/sceSifInitIopHeap.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
extern int D_0034A6B4;
extern RpcCD D_004CC800;
int func_00295D28(RpcCD *, unsigned int, int);
int func_00297850(void)
{
    int i;
    for (;;) {
        if (func_00295D28(&D_004CC800, 0x80000003, 0) < 0)
            return -1;
        if (D_004CC800.server != 0)
            break;
        i = 0x100000;
        while (i--)
            ;
    }
    D_0034A6B4 = 0;
    __asm__ __volatile__(""); /* emulates Sony scheduler: keep the store before the return-value set */
    return 0;
}
