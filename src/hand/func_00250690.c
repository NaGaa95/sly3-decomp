// Initialize the explicit owner record and set its original kind-five table.
// Reference algorithm: src/hand/func_00146EE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00349890[];
struct R { char prefix[0x70]; int kind; void *table; };
void func_001F3D48(void *owner,struct R *record);
void func_00250690(void *owner,struct R *record)
{
    func_001F3D48(owner,record);
    record->kind=5;
    record->table=D_00349890;
}
