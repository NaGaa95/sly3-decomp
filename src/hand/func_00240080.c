// Visit every 0xD0-byte entry with the selected key and invoke the alternate entry operation.
// Reference algorithm: src/hand/func_001F6AC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { int pad[4]; int k; char pad2[0xD0 - 0x14]; };
struct P { char pad[0xD0]; int c; struct E *ae; };
void func_0023B978(struct P *, struct E *);
void func_00240080(struct P *p, int k)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i]; if (pe->k == k) func_0023B978(p, pe);
    }
}
