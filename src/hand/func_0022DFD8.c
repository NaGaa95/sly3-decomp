// Return the last float in the original stored count/array pair.
// Reference algorithm: src/hand/func_00221120.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0xD8]; int count; int reserved;float *values; };
float func_0022DFD8(struct S *object)
{
    return object->values[object->count-1];
}
