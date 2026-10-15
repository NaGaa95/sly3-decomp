// Actual fixed-pool pointer return, verified with complete original callers and allocator.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_004799D0[];
extern void *func_0011E118(void *pool);
void *func_0012F240(unsigned int requested_bytes) { return func_0011E118(D_004799D0); }
