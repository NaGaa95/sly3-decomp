// Sly 2 reference: src/hand/func_0013F810.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int f0; int f4; char pad[0x20]; };
extern struct E D_0032CA80[];
int func_00119178(void *);
void func_00150AE8(void *, struct E *, int, void *);
void func_001519C8(void *p, void *pbis) {
    int n;
    while ((n = func_00119178(pbis)) >= 0) {
        struct E *pe = &D_0032CA80[n];
        func_00150AE8(p, pe, pe->f4 & 0x2580, pbis);
    }
}
