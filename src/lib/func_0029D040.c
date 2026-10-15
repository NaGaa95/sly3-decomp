// Reference: Sly 2 src/lib/__get_eh_info.c; target Sly 3 0x0029D040.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
extern void *(*get_eh_context)(void);
void *__get_eh_info(void) { return (char *)(*get_eh_context)() + 8; }
