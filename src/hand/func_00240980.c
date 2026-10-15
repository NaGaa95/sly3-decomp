// Release the original count10 receiver, clear all retained references and delete it with flags3 when nonpositive. Actual cleanup receivers and deletion flags are explicit.
// Reference algorithm: src/hand/func_001B3130.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4]; void * script; char unknown_8[0x8]; int references; };
void func_002BAA50(void *reference,void *actor);
void func_002BBF40(void *reference,void *script);
void func_0013BDE0(void *receiver);
void func_002BF240(void *receiver,int flags);
void func_00240980(struct S *p){if(--p->references<=0){func_002BAA50(p,0);func_002BBF40(&p->script,0);func_0013BDE0(p);if(p)func_002BF240(p,3);}}
