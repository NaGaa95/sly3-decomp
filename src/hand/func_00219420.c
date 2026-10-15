// Append one 16-byte record to the bounded eight-entry array.
// Reference algorithm: src/hand/func_001C2148.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { qword q; };
struct S { char pad[0x46C]; int c; struct E a[8]; };
void func_00219420(struct S *p, qword q)
{
    if ((unsigned)p->c < 8) { struct E *pe = &p->a[p->c++]; pe->q = q; }
}
