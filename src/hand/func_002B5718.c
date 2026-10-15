// Set the explicit 16-bit selection and notify the owning object.
// Reference algorithm: src/hand/func_0019E9D8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char pad[0x18]; short selection; short unknown; int value; };
struct S { char pad[0x20]; void *owner; struct R *record; };
void func_0023DD40(void *owner);
void func_002B5718(struct S *p, int value)
{
    p->record->selection = value;
    func_0023DD40(p->owner);
}
