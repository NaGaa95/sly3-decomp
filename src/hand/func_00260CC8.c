// Clear collection and selection state, reset the embedded list, and clear the associated control fields.
// Reference algorithm: src/hand/func_00212780.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct C { char pad[0x44]; int a; int b; };
struct S { char pad[0x38]; int x48; int x4c; int x50; int x54; char pad2[0x28]; short x80; short pad3; int x84; char pad4[0x38]; struct C *pc; char pad5[0x38]; int xf8; int unknownF0; char xfc[4]; };
void func_0011AD70(void *p);
void func_00260CC8(struct S *p)
{
    struct C *pc;
    p->xf8 = 0;
    p->x50 = 0;
    p->x54 = 0;
    p->x80 = 0;
    p->x84 = 0;
    func_0011AD70(p->xfc);
    pc = p->pc;
    pc->a = 0;
    pc->b = 0;
}
