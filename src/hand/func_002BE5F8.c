// Return the128-bit value in the record obtained through the original adjusted virtual getter.
// Reference algorithm: src/hand/func_00221268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct R { char prefix[0x30]; QWORD value; };
struct PMF { short adjustment; short unused; struct R *(*method)(void *); };
struct S { char prefix[0xC]; struct PMF *vtable; };
QWORD func_002BE5F8(struct S *object)
{
    struct PMF *slot = object->vtable + 36;
    return slot->method((char *)object + slot->adjustment)->value;
}
