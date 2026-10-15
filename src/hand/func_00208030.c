// Invoke the original empty inherited stub, then add the explicit object value to the receiver value for property69. Empty1F48F8 consumes no incoming argument; other helper inputs are all explicit.
// Reference algorithm: src/hand/func_00160C80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Other {char prefix[0x1AC];int value;};
void func_001F48F8(void);
int func_0013B500(void *object,int property);
int func_001F43C8(void *receiver);
void func_001F43D0(void *receiver,int value);
void func_00208030(void *receiver,struct Other *other){func_001F48F8();if(func_0013B500(other,0x69))func_001F43D0(receiver,func_001F43C8(receiver)+other->value);}
