// Update the inherited state and initialize the embedded record from its stored owner.
// Reference algorithm: src/hand/func_00174920.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x134]; void *owner; char unknown[0x24C - 0x138]; char record[1]; };
void func_001A9878(struct S *p, void *owner);
void func_001A99D0(void *record, void *owner);
void func_002133E8(struct S *p, void *owner)
{
    func_001A9878(p, owner);
    func_001A99D0(p->record, p->owner);
}
