// Initialize the inherited receiver and apply its original resource type, float control and absent selector before the enabled update.
// Reference algorithm: src/hand/func_001885B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xD8]; unsigned int type; float control; char unknown_E0[0x4]; int selection; };
void func_0028FD70(struct S *p);
void func_001C9118(struct S *p,int option);
void func_0026F970(struct S *p){func_0028FD70(p);p->type=0x0200017Eu;p->control=25.0f;p->selection=-1;func_001C9118(p,1);}
