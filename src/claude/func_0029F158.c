// func_0029F158: sceGsResetPath variant (Sly 2 counterpart s1_sceGsResetPath, src/lib/s1_sceGsResetPath.c, without the VIF1 wait loop).
// The VU0 FBRST access (cfc2/ctc2 $vi28) has no C equivalent; it is a small volatile asm as in Sly 2's source.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef int u_long128 __attribute__((mode(TI)));
extern u_long128 D_0034C300[2];
void func_0029F158(void)
{
    register int tmp __asm__("$4") = 0; /* the original keeps the VU0 FBRST value in $a0 */
    *(volatile int *)0x10003C10 = 1;
    *(volatile int *)0x10003C20 = 2;
    __asm__ volatile(
        
        "sync\n"
        "cfc2.ni %0, $vi28\n"
        "ori %0, %0, 0x200\n"
        "ctc2.ni %0, $vi28\n"
        "sync.p\n"
        : "=r"(tmp) : "0"(tmp));
    *(volatile u_long128 *)0x10005000 = D_0034C300[0];
    *(volatile u_long128 *)0x10005000 = D_0034C300[1];
    *(volatile int *)0x10003000 = 1;
}
