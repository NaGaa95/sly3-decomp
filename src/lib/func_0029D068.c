// Reference: Sly 2 src/lib/eh_context_initialize.c; target Sly 3 0x0029D068.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
extern void *(*get_eh_context)(void);
void *eh_context_static(void);
void *eh_context_initialize(void)
{
    get_eh_context = eh_context_static;
    return (*get_eh_context)();
}
