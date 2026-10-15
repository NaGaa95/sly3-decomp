// Apply the inherited receiver update and notify its original global resource for the actual two-state condition.23BBE0->1C7938 consumes receiver only before internal call setup;21A450 consumes both explicit pointers.
// Reference algorithm: src/hand/func_0017DDE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern void *D_00468D24;
struct S { char unknown_0[0x1B0]; int first; char unknown_1B4[0x364]; int second; };
void func_0023BBE0(void *receiver);
void func_0021A450(void *resource,void *receiver);
void func_00213FD0(struct S *p){func_0023BBE0(p);if(p->first==7 && p->second==2)func_0021A450(D_00468D24,p);}
