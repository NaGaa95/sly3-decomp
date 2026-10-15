// Apply the inherited reset and initialize both original command-mask ranges.
// Reference algorithm: src/hand/func_001DA808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0023AE08(void *p);
void func_00240E58(void *p,unsigned int mask,int value);
void func_00287A70(void *p){func_0023AE08(p);func_00240E58(p,0x03FFFFFFu,2);func_00240E58(p,0x03D88001u,0);}
