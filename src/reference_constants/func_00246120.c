// Reference algorithm: src/hand/func_001FC270.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x44]; int n40; char pad2[0x5C - 0x48]; unsigned short fl; unsigned short c52; char pad3[0x68 - 0x60]; long l68; char pad4[0x3BC - 0x70]; int n3BC; };
void func_00244CD0(struct P *);
void func_00246120(struct P *p)
{
    int f = 0; if (!p->n40) { f = p->c52 || (p->fl & 1); f ^= 1; } if (f) {
        func_00244CD0(p);
        p->l68 = 0;
        p->n3BC = 0xF;
    }
}
