// Reference algorithm: src/hand/func_001FBFB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VT { int pad[2]; short d; short p; void (*pfn)(void *); };
struct X { char pad[0xC]; struct VT *pvt; char pad2[0x44 - 0x10]; void *p40; char pad3[0x5C - 0x48]; unsigned short fl; };
void D_00245998(void);
void func_00291148(void *, void (*)(void), void *);
void func_00245320(struct X *, int, int);
void func_00245E78(struct X *px)
{
    if (px->fl & 0x400) {
        px->pvt->pfn((char *)px + px->pvt->d);
        func_00291148(px->p40, D_00245998, px);
        func_00245320(px, 0x400, 0);
    }
}
