// Reference: Sly 2 src/lib/__terminate.c; target Sly 3 0x0029CF60.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
extern void (*__terminate_func)(void);
void __terminate(void) { (*__terminate_func)(); }
