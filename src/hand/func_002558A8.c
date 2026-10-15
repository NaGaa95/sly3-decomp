// Find the original property200 attached receiver, initialize the complete16-byte command, set kind6 and actual incoming value A1, then dispatch it. Both dispatcher arguments and every fill/lookup input are explicit.
// Reference algorithm: src/hand/func_00171CF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Command {int kind;int value;int unknown[2];} __attribute__((aligned(16)));
void *func_002387A8(void *receiver,int property);
void *func_00292034(void *destination,int value,unsigned int count);
void func_0019A2D0(void *receiver,struct Command *command);
void func_002558A8(void *receiver,int value){void *object=func_002387A8((char *)receiver+0x29C,200);struct Command command;func_00292034(&command,0,16);command.value=value;command.kind=6;func_0019A2D0(object,&command);}
