// Initialize the absent selection and original global float value.
// Reference algorithm: src/hand/func_00210990.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
extern float D_0036BBD8;
struct S { char unknown_0[0x50]; int selection; float value; };
void func_0021EE50(struct S *object)
{
    object->selection=-1;object->value=D_0036BBD8;
}
