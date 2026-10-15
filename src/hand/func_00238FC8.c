// Run the inherited update and enable flag 0x80 in the owner flag word.
// Reference algorithm: src/hand/func_001C2048.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; unsigned flags; };
void func_001C7340(struct S *p);
void func_00238FC8(struct S *p)
{
    func_001C7340(p);
    p->flags |= 0x80;
}
