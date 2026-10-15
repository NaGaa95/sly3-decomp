// Return the original Boolean acceptance of either receiver control or exact global state1; no additional input is consumed.
// Reference algorithm: src/hand/func_00209098.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern int D_004C4090;
struct S { char unknown_0[0x4344]; int first; char unknown_4348[0xDC]; int second; };
int func_0025AE28(struct S *p){if(p->first)return 1;if(p->second)return 1;return D_004C4090==1;}
