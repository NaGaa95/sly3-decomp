// Reference algorithm: src/hand/func_001FCBA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[8]; };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x44 - 0x10]; int f40; char pad3[0x5C - 0x48]; unsigned short fl; short s52; };
void func_00244C70(struct X *);
void func_00245320(struct X *, int, int);
#define VF(q, n) (q)->pvt->a[n].pfn((char *)(q) + (q)->pvt->a[n].d)
void func_00246A40(int f, long l)
{
    struct X *px = (struct X *)l;
    px->f40 = f;
    if (f) func_00245320(px, 0x1000, 0x1000);
    else {
        func_00244C70(px);
        px->s52 = 0;
        if (!(px->fl & 8)) VF(px, 7);
    }
    VF(px, 2);
}
