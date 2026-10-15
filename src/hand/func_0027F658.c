// Apply the inherited receiver reset, set the active state, issue the explicit embedded command and set the original mask.15CB98 consumes only receiver through its initial28FD70 path;15C4A8 consumes record and command.
// Reference algorithm: src/hand/func_0014A200.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x244]; int state; char unknown_248[0xC]; unsigned int mask; };
void func_0015CB98(void *receiver);
void func_0015C4A8(void *record,int command);
void func_0027F658(struct S *p){func_0015CB98(p);p->state=1;func_0015C4A8((char *)p+0x120,0x3A);p->mask=0x03FFFFFF;}
