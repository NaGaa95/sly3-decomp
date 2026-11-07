// Sly 2 counterpart: new_eh_context (decomp src/lib/new_eh_context.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
struct eh_context { void *handler_label; void **dynamic_handler_chain; void *info; void *table_index; };
void *func_001D27E0(unsigned long);
void *func_00292034(void *, int, unsigned long);
void __terminate(void);
struct eh_context *func_0029CFC0(void)
{
    struct eh_context *ehc;
    struct eh_full_context { struct eh_context c; void *top_elt[2]; } *ehfc =
        (struct eh_full_context *)func_001D27E0(sizeof *ehfc);
    if (!ehfc)
        __terminate();
    func_00292034(ehfc, 0, sizeof *ehfc);
    ehc = (struct eh_context *)ehfc;
    if ((void *)(&ehc->dynamic_handler_chain) != (void *)ehc)
        ;
    ehc->dynamic_handler_chain = (void **)ehfc->top_elt;
    return ehc;
}
