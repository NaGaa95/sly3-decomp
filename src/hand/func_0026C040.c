// Release all four original embedded references after the inherited cleanup and clear the derived state.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x278]; int state; };
void func_001F3C80(struct S *p);
void func_00137628(void *record);
void func_0026C040(struct S *p){func_001F3C80(p);func_00137628((char *)p+0x2BC);func_00137628((char *)p+0x2B8);func_00137628((char *)p+0x2B4);func_00137628((char *)p+0x2B0);p->state=0;}
