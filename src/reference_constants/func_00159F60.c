// Reference algorithm: src/hand/func_00147338.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int a; int b; int k; };
struct P { char pad[0x140]; int id; int f164; int f168; int f16C; int x170; };
void func_0013BEC0(struct P *p, int kind, struct MSG *pmsg);
void func_0015A038(struct P *p, int n);
void func_00159F60(struct P *p, int kind, struct MSG *pmsg)
{
    func_0013BEC0(p, kind, pmsg);
    if (kind != 10) return;
    if (pmsg->a != p->id) return;
    switch (pmsg->k) {
    case 0x6CC: p->f164 = 1; break;
    case 0x6CD: p->f164 = 0; break;
    case 0x6CE: p->f168 = 1; break;
    case 0x6CF: p->f168 = 0; break;
    case 0x6D0: p->f16C = 0; break;
    case 0x6D1: p->f16C = 1; break;
    case 0x6D2:
        if (p->x170 != -1) func_0015A038(p, 3);
        break;
    }
}
