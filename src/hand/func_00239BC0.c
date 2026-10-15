// Release the original retained receiver when count10 becomes nonpositive, clear actor/script/messages and return it to its actual fixed pool. Every consumed cleanup input is explicit.
// Reference algorithm: src/hand/func_001B3130.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4]; void * script; char unknown_8[0x8]; int references; };
void func_002BAA50(void *reference,void *actor);
void func_002BBF40(void *reference,void *script);
void func_0013BDE0(void *receiver);
extern char D_00479A14[];
void func_0011E1F0(void *pool,void *allocation);
void func_00239BC0(struct S *p){if(--p->references<=0){func_002BAA50(p,0);func_002BBF40(&p->script,0);func_0013BDE0(p);func_0011E1F0(D_00479A14,p);}}
