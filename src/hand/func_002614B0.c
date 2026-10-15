// Apply the inherited receiver update and pass the actual Boolean state to both state helpers when active. Complete1FCAC8 consumes only incoming receiver and sets all its virtual arguments internally.
// Reference algorithm: src/hand/func_00139318.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xA0]; int active; char unknown_A4[0xC]; int state; };
void func_001FCAC8(void *receiver);
void func_00261050(void *receiver,int state);
void func_00261070(void *receiver,int state);
void func_002614B0(struct S *p){func_001FCAC8(p);if(p->active){int state=!p->state;func_00261050(p,state);func_00261070(p,state);}}
