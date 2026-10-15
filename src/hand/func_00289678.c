// Reset the inherited receiver, initialize the two absent selectors and float default, configure the original linked list and activate the object. All actual receiver/list/selector inputs are explicit.
// Reference algorithm: src/hand/func_0017DDE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x40]; float value; char unknown_44[0x8]; int first; char unknown_50[0x410]; int second; };
void func_001C7340(void *receiver);
void func_0011AD60(void *list,int next_offset);
void func_001C9118(void *receiver,int active);
void func_00289678(struct S *p){func_001C7340(p);p->value=-1.0f;p->second=-1;p->first=-1;func_0011AD60((char *)p+0x678,0xA4);func_001C9118(p,1);}
