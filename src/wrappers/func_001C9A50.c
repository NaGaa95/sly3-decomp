// SLY3_CFLAGS: -Os -G0
// Factory callers pass an object byte count; this original fixed-pool wrapper
// ignores that request and returns the pointer from the pool allocator.
extern unsigned char D_00479DF0[];
extern void *func_0011E118(void *pool);
void *func_001C9A50(unsigned int requested_bytes) {
    return func_0011E118(D_00479DF0);
}
