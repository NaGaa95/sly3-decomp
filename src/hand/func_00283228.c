// Apply the inherited receiver update, resolve its identifier with all four original resource inputs, and insert the receiver into the returned resource list. Complete1C7DC8->1C7F18 consumes only incoming receiver A0 before internal explicit call setup.
// Reference algorithm: src/hand/func_0012E6E8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char unknown_0[0x48]; int id; };
void func_001C7DC8(void *p);
void *func_0017E1B8(void *global,int kind,int id,void *owner);
void func_0011AD80(void *list,void *node);
void func_00283228(struct S *p){void *resource;func_001C7DC8(p);resource=func_0017E1B8(D_00475480,5,p->id,0);if(resource)func_0011AD80((char *)resource+0x8C,p);}
