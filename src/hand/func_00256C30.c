// Reset the embedded sixteen-byte command, store both explicit integer inputs and resolve it against the stored owner.254BB8 consumes only record A0; owner A1 is retained as a caller-derived unused formal.254C00 consumes both explicit pointers.
// Reference algorithm: src/hand/func_00171AF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Command { int kind;int value;int unknown;int mode; };
struct S { char prefix[0xA8];void *owner;int unused;struct Command command; };
void func_00254BB8(struct Command *record,void *owner);
void func_00254C00(struct Command *record,void *owner);
void func_00256C30(struct S *p,int value,int mode){struct Command *record=&p->command;func_00254BB8(record,p->owner);p->command.value=value;p->command.mode=mode;func_00254C00(record,p->owner);}
