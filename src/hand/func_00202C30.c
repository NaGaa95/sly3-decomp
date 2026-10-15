// Release the original count88 retained object, actor/script references and messages, deleting it with flags3 when the decremented count is nonpositive. Every cleanup input is explicit.
// Reference algorithm: src/hand/func_001B3130.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4]; void * script; char unknown_8[0x80]; int references; };
void func_002BAA50(void *reference,void *actor);
void func_002BBF40(void *reference,void *script);
void func_0013BDE0(void *receiver);
void func_002BEAD8(void *receiver,int flags);
void func_00202C30(struct S *p){if(--p->references<=0){func_002BAA50(p,0);func_002BBF40(&p->script,0);func_0013BDE0(p);if(p)func_002BEAD8(p,3);}}
