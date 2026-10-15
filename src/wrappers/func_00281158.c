// Actual fixed-pool pointer return, verified with complete original callers and allocator.
// SLY3_CFLAGS: -Os -G0

extern void *func_0011E118(void *pool);
void *func_00281158(void *a0) { return func_0011E118(((char *)(a0) + (18676))); }
