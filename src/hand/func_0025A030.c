// Complete word setter explicitly consumes receiverA0 and valueA1, storing that value atC. No other incoming register or callee is present.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
struct O {char prefix[0xC];int value;};
void func_0025A030(struct O *object,int value){object->value=value;}
