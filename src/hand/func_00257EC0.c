// Complete state setter consumes receiver A0 and explicit integer state A1, storing original field16EC.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
struct Object {char prefix[0x16EC];int state;};
void func_00257EC0(struct Object *object,int state){object->state=state;}
