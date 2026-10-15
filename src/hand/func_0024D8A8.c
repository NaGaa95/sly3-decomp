// Initialize the inherited object, scale fields, selection and new enabled flag, then set the default timer and embedded collection owner.
// Reference algorithm: src/hand/func_00203948.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x210]; float g200; char p1[0x1C]; float g214; char p2[8]; float g220; char p3[0x50]; float g260; int n264; char p4[4]; char x26C[4]; };
void func_0023B5C0(struct S *p, int enabled);
void func_001F3B50(struct S *p);
void func_0024F188(struct S *p, float g);
void func_0024E878(struct S *p, float g);
void func_002384F8(void *pv, struct S *p);
void func_0024D8A8(struct S *p)
{
    func_001F3B50(p);
    p->n264 = -1;
    p->g260 = 1.0f;
    p->g200 = 1.0f;
    func_0024F188(p, 1.0f);
    func_0024E878(p, 0.0f);
    func_0023B5C0(p, 1);
    p->g214 = 30.0f;
    func_002384F8(p->x26C, p);
}
