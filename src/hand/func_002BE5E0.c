// Complete Boolean getter consumes only receiver A0 and returns original64-bit flags28 bit56. Explicit integer conversion preserves the complete original zero/sign-extension instructions. Preceding unrelated fragments remain excluded.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
struct Object {char prefix[0x28];unsigned long flags;};
int func_002BE5E0(struct Object *object){return (int)(object->flags>>56)&1;}
