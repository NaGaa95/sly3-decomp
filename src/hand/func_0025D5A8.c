// Return the next12-byte entry and increment the corresponding stored count.
// Reference algorithm: src/hand/func_00120840.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int words[3]; };
struct S { char prefix[0x3F00]; struct E *entries; int count; };
struct E *func_0025D5A8(struct S *object)
{
    return object->entries+object->count++;
}
