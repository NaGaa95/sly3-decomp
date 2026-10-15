// Reset the inherited state, initialize the embedded attachment from its owner, and mark the attachment active.
// Reference algorithm: src/hand/func_00155560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x28]; void *owner; char pad2[4]; char attachment[0xBC]; int active; };
void func_00169E28(struct S *p);
void func_001F3CB8(void *owner, void *attachment);
void func_00274760(struct S *p)
{
    func_00169E28(p);
    func_001F3CB8(p->owner, p->attachment);
    p->active = 1;
}
