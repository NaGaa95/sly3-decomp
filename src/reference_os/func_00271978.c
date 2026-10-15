// Sly 2 reference: src/hand/UpperizePchz__FPc.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0032A691[];
void func_00271978(char *pchz)
{
    unsigned char *pch;
    for (pch = (unsigned char *)pchz; *pch; pch++) {
        int c = *pch;
        int u = c - 0x20;
        if (!(D_0032A691[c] & 2))
            u = c;
        *pch = u;
    }
}
