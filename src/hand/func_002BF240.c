// Run the original base destructor with zero flags and release the receiver when requested by the explicit flags.
// Reference algorithm: src/hand/FUN_0018d2e8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002BC7F0(void *p,int flags);
void func_00240A00(void *p);
void func_002BF240(void *p,int flags){func_002BC7F0(p,0);if(flags&1)func_00240A00(p);}
