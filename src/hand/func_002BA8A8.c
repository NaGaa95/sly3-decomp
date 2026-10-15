// Run the original base destructor with zero flags and return the receiver to its actual pool if requested; base and pool operations express both actual inputs.
// Reference algorithm: src/hand/func_001E1560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_004D2AD8[];
void func_002BA960(void *receiver,int flags);
void func_0011E1F0(void *pool,void *receiver);
void func_002BA8A8(void *receiver,int flags){func_002BA960(receiver,0);if(flags&1)func_0011E1F0(D_004D2AD8,receiver);}
