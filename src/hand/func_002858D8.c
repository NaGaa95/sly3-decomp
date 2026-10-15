// Forward the original incoming selection A1, then change active state only if the receiver is absent from both global selections. Each direct helper consumes both explicit inputs.
// Reference algorithm: src/hand/func_0017DDE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x190]; int state; };
void func_001F4548(void *receiver,int selection);
int func_001F4350(void *receiver,int selection);
void func_00286360(void *receiver,int state);
void func_002858D8(struct S *p,int selection){func_001F4548(p,selection);if(!func_001F4350(p,-1)&&p->state==1)func_00286360(p,2);}
