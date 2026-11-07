// Sly 2 counterpart: sceDmaPause (decomp src/lib/sceDmaPause.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
// (Claude agent) near miss: 2/38 with 114+macro
typedef struct { unsigned DIR:1; unsigned p0:1; unsigned MOD:2; unsigned ASP:2; unsigned TTE:1; unsigned TIE:1; unsigned STR:1; unsigned p1:7; unsigned TAG:16; } tD_CHCR;
typedef struct { tD_CHCR chcr; unsigned p0[3]; void *madr; unsigned p1[3]; unsigned qwc; unsigned p2[3]; void *tadr; } sceDmaChan;
int func_002980D0(void);
int func_00298120(void);
#define D_ENABLER (*(volatile unsigned *)0x1000F520)
#define D_ENABLEW (*(volatile unsigned *)0x1000F590)
#define D_CTRL (*(volatile unsigned *)0x1000E000)
unsigned func_0029FE28(sceDmaChan *d)
{
    int e = func_002980D0();
    unsigned en = D_ENABLER;
    unsigned c, ctrl;
    if (!(en & 0x10000)) D_ENABLEW = en | 0x10000;
    ctrl = D_CTRL;
    c = *(volatile unsigned *)d;
    *(volatile unsigned *)d = c & ~0x100;
    D_ENABLEW = en;
    if (e) func_00298120();
    return c;
}
