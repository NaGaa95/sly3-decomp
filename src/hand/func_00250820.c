// Initialize the original global resource once through all four explicit allocation inputs; no incoming register is consumed by this initializer.
// Reference algorithm: src/hand/func_00152100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern void *D_00475470;
void *func_00150690(int kind,void *owner,int id,int option);
void func_00250820(void){if(!D_00475470)D_00475470=func_00150690(0x92,0,0x748,-1);}
