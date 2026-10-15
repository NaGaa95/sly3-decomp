// Run the original base destructor with zero flags and release the receiver when requested by the explicit flags.
// Reference algorithm: src/hand/FUN_0018d2e8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002BF578(void *p,int flags);
void func_00246B90(void *p);
void func_002BF528(void *p,int flags){func_002BF578(p,0);if(flags&1)func_00246B90(p);}
