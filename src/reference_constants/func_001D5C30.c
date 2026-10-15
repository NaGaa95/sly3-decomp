// Reference algorithm: src/hand/func_001B0E28.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; };
extern struct CLOCK D_0036BB98;
extern float D_00324290;
struct S { char pad[0x148]; float f168; int x16C; char pad1[0x1C4 - 0x170]; int x1C4; char pad2[0x220 - 0x1C8]; int x220; int x224; float f228; float f22C; };
void func_0023C660(struct S *p);
int func_001D66D0(struct S *p);
int func_001D6658(struct S *p);
void func_002412C8(struct S *p, float f);
void func_001D6110(struct S *p, int st);
void func_001D5F38(struct S *p);
void func_001D5C30(struct S *p)
{
    int st;
    func_0023C660(p);
    st = p->x220;
    switch (st) {
    case 0:
        st = func_001D66D0(p);
        if (st != 3 && p->f228 <= D_0036BB98.t) {
            if (p->x16C) st = 1;
        }
        break;
    case 1:
        st = func_001D66D0(p);
        if (st != 3 && p->f228 <= D_0036BB98.t) st = 0;
        break;
    case 2:
        st = func_001D66D0(p);
        if (st != 3 && func_001D6658(p)) st = 1;
        break;
    case 3:
        if (!p->x1C4 && func_001D6658(p)) st = 4;
        break;
    case 4:
        if (p->f22C <= D_0036BB98.t) {
            func_002412C8(p, p->f168);
            p->f22C = D_00324290;
        }
        break;
    }
    func_001D6110(p, st);
    func_001D5F38(p);
}
