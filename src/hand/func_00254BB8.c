// Release the original kind3 pointer and invalidate both command words. The historically supplied owner A1 is unused by the complete body and retained provisionally for consistency with existing callers.
// Reference algorithm: src/hand/func_001BBA18.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Command {int kind;int value;};
void func_002595B0(void *value);
void func_00254BB8(struct Command *p,void *owner){if(p->kind==3){func_002595B0((void *)p->value);p->value=0;}p->value=-1;p->kind=-1;}
