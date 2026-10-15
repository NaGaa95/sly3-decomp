// Reset the receiver and forward both explicit source/matrix pointers to its original transformation helper, whose full body consumes all three GP inputs.
// Reference algorithm: src/hand/func_00129970.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00256DF0(void *receiver);
void func_0024F6F8(void *receiver,void *source,void *matrix);
void func_00257678(void *receiver,void *source,void *matrix){func_00256DF0(receiver);func_0024F6F8(receiver,source,matrix);}
