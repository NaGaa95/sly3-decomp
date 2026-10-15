// Commit the record state, then update the owning object stored in its first field.
// Reference algorithm: src/hand/func_001C3DC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { void *owner; };
void func_00169E40(struct S *record);
void func_00166548(void *owner);
void func_00210760(struct S *record)
{
    func_00169E40(record);
    func_00166548(record->owner);
}
