// SLY3_CFLAGS: -Os -G0
// Set the 2-bit mode at bit 56 of the flags word (+0x120); entries in the old/new state get their values swapped.
struct E { char pad[0x18]; short n18; char pad1A[2]; int n1C; char pad20[0xD0 - 0x20]; };
struct S
{
    char pad0[0xD0];
    int ce;
    struct E *ae;
    char padD8[0x120 - 0xD8];
    union {
        struct { unsigned long pad120 : 56; unsigned long k : 2; unsigned long pad127 : 6; } f;
        struct { unsigned long pad120 : 56; unsigned long b127 : 8; } g;
        unsigned char ab[8];
    } u;
};
void func_00241150(struct S *p, int k)
{
    int n18, nOld, nNew, i;
    if (k == (p->u.g.b127 & 3))
        return;
    switch (k) {
    case 0:
    case 1:
    case 3:
        nOld = 0x10000;
        nNew = 0;
        n18 = 10;
        break;
    case 2:
        n18 = p->u.ab[4];
        nOld = 0;
        nNew = 0x10000;
        break;
    }
    for (i = 0; i < p->ce; i++) {
        struct E *pe = &p->ae[i];
        if (pe->n1C == nOld) {
            pe->n1C = nNew;
            pe->n18 = n18;
        }
    }
    p->u.f.k = k;
}
