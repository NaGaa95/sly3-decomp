// Actual fixed-pool pointer return, verified with complete original callers and allocator.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475024[];
extern void *func_0011E118(void *pool);
void *func_00246B70(unsigned int requested_bytes) { return func_0011E118(D_00475024); }
