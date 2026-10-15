// Allocation forwards fixed pool00479CB0 A0 to11E118 and returns actual pointer; original incoming A0 is overwritten before read. Unsigned requested-size formal is caller-proved from original immediate F0/100/110 request sizes and unused by this fixed-pool body.
// SLY3_CFLAGS: -Os -G0
extern char D_00479CB0[];
void *func_0011E118(void *pool);
void *func_0020BB90(unsigned int requested_bytes){return func_0011E118(D_00479CB0);}
