// Sly 2 reference: src/hand/func_001FB710.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VT { int pad[4]; short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; struct VT *pvt; };
struct DL;
extern struct DL D_0047503C;
int func_0011B0C0(struct DL *, void *);
void func_0011B028(struct DL *, void *);
void func_002453D8(struct X *px)
{
    if (func_0011B0C0(&D_0047503C, px)) {
        func_0011B028(&D_0047503C, px);
        px->pvt->pfn((char *)px + px->pvt->d);
    }
}
