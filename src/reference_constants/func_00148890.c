// Reference algorithm: src/hand/func_001383F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x80]; float f80; float f84; void *f88; void *f8c; char pad2[0x9a - 0x90]; short f9a; };
struct C { int f0; int f4; struct X *px; char pad[0x1c - 0xc]; int f1c; char pad2[0x28 - 0x20]; struct C *pnext; };
struct A { char pad[0x2c]; struct A *pnext; int f30; struct C *pcFirst; };
struct S { char pad[0x40]; struct A *paFirst; char pad2[0xd4 - 0x54]; int fd4; };
extern const float D_00320200;
extern char D_0034A150[];
int func_0012F2D0(struct C *);
void func_00148890(struct S *p, int n) {
    struct A *pa;
    struct C *pc;
    if (n == p->fd4) return;
    p->fd4 = n;
    for (pa = p->paFirst; pa; pa = pa->pnext) {
        for (pc = pa->pcFirst; pc; pc = pc->pnext) {
            if (pc->f1c && func_0012F2D0(pc)) {
                struct X *px = pc->px;
                px->f80 = px->f84 = D_00320200; px->f88 = px->f8c = D_0034A150; px->f9a = 0;
            }
        }
    }
}
