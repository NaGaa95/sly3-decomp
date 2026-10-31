// Fixed-capacity (6 entries) list adders: add an object pointer to an entry, or store a position vector.
// Reference algorithm: Sly 2 src/hand/func_001C20E8.c and func_001C2148.c.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { void *p0; void *p4; int pad[2]; qword q; };
struct S { char pad[0x40]; int c; char pad2[0xC]; struct E a[6]; };
int func_0013B500(void *q, int n);

void func_001EE9A0(struct S *p, void *q)
{
    if ((unsigned)p->c < 6) {
        struct E *pe = &p->a[p->c++];
        if (func_0013B500(q, 9)) pe->p0 = q; else pe->p4 = q;
    }
}

void func_001EEA00(struct S *p, qword q)
{
    if ((unsigned)p->c < 6) { struct E *pe = &p->a[p->c++]; pe->q = q; }
}
