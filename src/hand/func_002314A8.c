// Copy the stored word array into the receiver destination through the original byte-copy API.
// Reference algorithm: src/hand/func_00221268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0xD8]; int count; int unknown; void *data; };
struct S { char prefix[0x48]; struct R *record; char unknown[0x10]; void *destination; };
void func_001D2898(void *destination, void *source, int size);
void func_002314A8(struct S *object)
{
    func_001D2898(object->destination, object->record->data, object->record->count * sizeof(int));
}
