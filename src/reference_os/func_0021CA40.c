// Sly 2 reference: src/hand/func_001D8640.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0032A691[];
static inline int ToUpper(int c) { return (D_0032A691[c] & 2) ? c - 0x20 : c; }
int func_0021CA40(unsigned char *pch) {
    int h = 0;
    while (*pch) {
        h = h * 33 + ToUpper(*pch);
        pch++;
    }
    return h;
}
