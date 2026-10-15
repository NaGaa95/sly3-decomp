// Reset the explicit receiver and original global collection, applying both original receiver-processing flags.
// Reference algorithm: src/hand/func_001DA808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0013C958(void *p);
void func_002429C8(void);
void func_00242B90(void *p,int flags);
void func_00242A58(void *p){func_0013C958(p);func_002429C8();func_00242B90(p,1);func_0013C958(p);func_00242B90(p,6);}
