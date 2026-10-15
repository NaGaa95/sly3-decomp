// Reset a present owned resource control and clear the original embedded reference through its retaining assignment helper.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Ref { void *value; };
struct S { char prefix[0x3F4];struct Ref reference; };
void func_00244CA8(void *value,float control);
void func_002BBCD8(struct Ref *reference,void *value);
void func_002051F0(struct S *p){struct Ref *reference=&p->reference;if(reference && reference->value){func_00244CA8(reference->value,0.0f);func_002BBCD8(reference,0);}}
