// Reset the original embedded command and store both actual integer controls.254BB8 consumes command A0; owner A1 is caller-derived unused by its complete body and retained provisionally.
// Reference algorithm: src/hand/func_00129970.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Command {int kind;int value;int unknown;int mode;};
struct S {char prefix[0xA8];void *owner;int unused;struct Command command;};
void func_00254BB8(struct Command *record,void *owner);
void func_00256BE0(struct S *p,int value,int mode){func_00254BB8(&p->command,p->owner);p->command.value=value;p->command.mode=mode;}
