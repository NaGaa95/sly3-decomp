// Return the original three-state integer classification from the positive receiver float or its explicit signed stored-value getter;1F43C8 consumes receiver A0 only.
// Reference algorithm: src/hand/func_0014F6F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x39C]; float value; };
int func_001F43C8(void *receiver);
int func_00207DD8(struct S *p){if(!(0.0f<p->value))return func_001F43C8(p)>0?0:2;return 1;}
