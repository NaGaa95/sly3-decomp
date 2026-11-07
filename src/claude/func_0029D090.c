// Sly 2 counterpart: eh_context_static (decomp src/lib/eh_context_static.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
struct eh_context { void *handler_label; void **dynamic_handler_chain; void *info; void *table_index; };
void *func_00292034(void *, int, unsigned long);
extern struct eh_context D_004D0BD8;
extern int D_004D0BE8;
extern void *D_004D0BF0[2];
struct eh_context *func_0029D090(void)
{
    if (!D_004D0BE8) {
        D_004D0BE8 = 1;
        func_00292034(&D_004D0BD8, 0, sizeof D_004D0BD8);
        D_004D0BD8.dynamic_handler_chain = D_004D0BF0;
    }
    return &D_004D0BD8;
}
