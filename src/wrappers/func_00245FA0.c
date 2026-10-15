// Actual fixed-pool pointer return, verified with complete original callers and allocator.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0047500C[];
extern void *func_0011E118(void *pool);
void *func_00245FA0(unsigned int requested_bytes) { return func_0011E118(D_0047500C); }
