// Convert the explicit reference ID to a 16-byte mask, select its entry, and initialize four numeric fields in the 0x110-byte object.
// Reference algorithm: src/hand/func_00207C48.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct X { int a; char p0[0x3C]; int b; char p1[0x3C]; int c; char p2[0x3C]; int d; };
struct E { int k; struct X *px; int pad; int n; };
typedef struct { int words[4]; } MASK;
typedef struct { short tag; short pad; int value; } REF;
MASK *func_00252D80(MASK *out, REF *id);
struct E *func_002554C0(void *p, MASK *id);
struct X *func_00259590(int cb);
void func_002592A0(struct X *px);
void func_00253540(void *p, REF *id, int a, int b, int c, int d)
{
    MASK mask;
    struct E *pe;
    func_00252D80(&mask, id);
    pe = func_002554C0(p, &mask);
    pe->k = 3;
    pe->px = func_00259590(0x110);
    func_002592A0(pe->px);
    pe->px->a = a;
    pe->px->b = b;
    pe->px->c = c;
    pe->px->d = d;
    pe->n = 8;
}
