// Allocate the original fixed-size record and construct it with actual owner A1,tag A2 and object A3.169BF8 supplied size A0 is caller-derived unused by its fixed-pool body, retained provisionally; constructor uses all supplied inputs.
// Reference algorithm: src/hand/FUN_0018d2e8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void *func_00169BF8(unsigned int bytes);
void *func_0026DE78(void *receiver,void *owner,int tag,void *object);
void *func_0026C948(void *object,void *owner){void *receiver=func_00169BF8(0x24);return func_0026DE78(receiver,owner,9,object);}
