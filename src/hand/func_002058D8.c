// Return whether both original receiver predicates are false, preserving their short-circuit order.
// Reference algorithm: src/hand/func_001F82B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_00205A38(void *p);
int func_0023E130(void *p);
int func_002058D8(void *p){int result=0;if(!func_00205A38(p))result=!func_0023E130(p);return result;}
