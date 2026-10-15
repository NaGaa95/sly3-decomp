// Initialize the inherited object and set its absent selection and active flag.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x138]; int selection; char unknown[0x168 - 0x13C]; int active; };
void func_0028FD70(struct S *p);
void func_0022D708(struct S *p)
{
    func_0028FD70(p);
    p->selection = -1;
    p->active = 1;
}
