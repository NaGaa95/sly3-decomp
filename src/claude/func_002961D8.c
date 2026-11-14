// Sly 2 counterpart: new_iob (decomp src/lib/new_iob.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
struct iob { int x0, x4, x8, xC; };
extern int D_0034A6A8;
extern struct iob D_004CC500[];
void func_00296160(void);
int func_002936E0(int);
int func_002936C0(int);
struct iob *func_002961D8(void)
{
    struct iob *io;
    func_00296160();
    func_002936E0(D_0034A6A8);
    for (io = D_004CC500; io < D_004CC500 + 32; io++) {
        if (io->x4 == 0) {
            io->x4 = 0x10000000;
            func_002936C0(D_0034A6A8);
            return io;
        }
    }
    func_002936C0(D_0034A6A8);
    return 0;
}
