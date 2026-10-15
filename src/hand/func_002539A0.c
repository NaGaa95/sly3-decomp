// Reset all three original embedded command-record arrays through the same helper.
// Reference algorithm: src/hand/func_001492B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00253950(void *p,void *records);
void func_002539A0(void *p){func_00253950(p,(char *)p+0xE20);func_00253950(p,(char *)p+0xAE0);func_00253950(p,(char *)p+0xC80);}
