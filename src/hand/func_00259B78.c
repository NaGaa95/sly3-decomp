// Accept the flagged record property first or return the original receiver/record predicate, explicitly preserving both pointer inputs and the integer Boolean result.
// Reference algorithm: src/hand/func_0013C278.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {int unused;void *object;char unknown[0x18-8];unsigned long flags;};
int func_0013B500(void *object,int property);
int func_0025CEC8(void *receiver,struct Record *record);
int func_00259B78(void *receiver,struct Record *record){if((record->flags&0x10000)&&func_0013B500(record->object,0x65))return 1;return func_0025CEC8(receiver,record);}
