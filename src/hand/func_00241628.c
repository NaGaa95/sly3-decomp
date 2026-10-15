// Compare the actual incoming integer against original flag2, replace only its low bit when changed, and notify the receiver. The helper consumes only incoming receiver A0.
// Reference algorithm: src/hand/func_001F4BA8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x128];unsigned long flags;};
void func_0023EA88(void *receiver);
void func_00241628(struct S *p,int enabled){if(enabled!=((int)(p->flags>>2)&1)){p->flags=(p->flags&~4UL)|((unsigned long)(enabled&1)<<2);func_0023EA88(p);}}
