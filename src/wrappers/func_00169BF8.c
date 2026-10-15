// SLY3_CFLAGS: -Os -G0
// Factory callers pass an object byte count; this original fixed-pool wrapper
// ignores that request and returns the pointer from the pool allocator.
extern unsigned char D_0047931C[];
extern void *func_0011E118(void *pool);
void *func_00169BF8(unsigned int requested_bytes) {
    return func_0011E118(D_0047931C);
}
