// Destroy the embedded record with its original flag and conditionally invoke the caller-derived object release stub.
// Reference algorithm: src/hand/func_001E1560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002BFE68(void *record,int flags);
void func_001D2818(void *p);
void func_002C01F8(void *p,int flags){func_002BFE68((char *)p+0x60,2);if(flags&1)func_001D2818(p);}
