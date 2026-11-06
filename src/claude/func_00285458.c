// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; int f; char pad1[0x164 - 0x40]; int x164; char pad2[0x190 - 0x168]; int x190; int pad3; int x198; int pad4; int x1A0;
           char pad5[0x1D0 - 0x1A4]; float f1D0, f1D4, f1D8, f1DC, f1E0, f1E4, f1E8, f1EC; char pad6[0x1F8 - 0x1F0]; float f1F8;
           char pad7[0x220 - 0x1FC]; float f220; char pad8[0x2B0 - 0x224]; int x2B0; char pad9[0x2BC - 0x2B4]; int x2BC; char padA[0x2C4 - 0x2C0];
           int x2C4; char padB[0x2D0 - 0x2C8]; int x2D0; };
void func_001F3B50(struct S *p);
void func_001F43F8(struct S *p, int k);
void func_00240E58(struct S *p, int mask, int k);
static inline int FIsPtr(int f) { return !(f & 1); }
void func_00285458(struct S *p)
{
    int f;
    func_001F3B50(p);
    p->f1E0 = -0.2f;
    p->f1E4 = 0.2f;
    p->f1D0 = -1.2f;
    p->f1D4 = 1.2f;
    p->f1E8 = -0.2f;
    p->f1EC = 0.2f;
    p->f1F8 = 7.0f;
    p->f220 = 4.0f;
    p->f1D8 = 2.5f;
    p->f1DC = 0.8f;
    p->x2C4 = 0;
    func_001F43F8(p, 40);
    p->x2B0 = -1;
    p->x2D0 = -1;
    p->x2BC = 1;
    func_00240E58(p, 0x3FFFFFF, 2);
    func_00240E58(p, 0x3D88001, 0);
    f = p->f;
    p->x190 = -1;
    p->x198 = -1;
    p->x1A0 = -1;
    p->x164 = 2;
    if (FIsPtr(f)) *(int *)f |= 2;
    else p->f = f | 2;
}
