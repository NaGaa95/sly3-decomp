// Apply the inherited explicit object/record update and copy the receiver float value into that record.
// Reference algorithm: src/hand/func_001B34D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x220]; float value; };
struct R { char prefix[0x54];float value; };
void func_001F3D48(struct S *p,struct R *record);
void func_00214820(struct S *p,struct R *record){func_001F3D48(p,record);record->value=p->value;}
