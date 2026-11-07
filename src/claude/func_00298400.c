// Sly 2 counterpart: PatchIsNeeded (decomp src/lib/PatchIsNeeded.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
// (Claude agent) near miss: 3/26, prologue order only (target sd s0 before sd ra; Sony saves low regs first)
int func_00293750(unsigned int *);
int func_00293740(unsigned int *);
int func_00298400(void)
{
    unsigned int a, b;
    func_00293750(&a);
    b = (a & 0xFFFF1FFF) | 0x2000;
    func_00293740(&b);
    func_00293750(&b);
    func_00293740(&a);
    return ((b >> 13) & 7) == 0;
}
