// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct O { char pad[0x18]; int x18; };
struct S { char pad[0x130]; int x130; struct O *x134; char pad138[0x190 - 0x138]; int x190; int pad194; int x198; int pad19c; int x1A0;
           char pad1a4[0x1AC - 0x1A4]; int x1AC; char pad1b0[0x2B8 - 0x1B0]; int x2B8; int x2BC; char pad2c0[0x2D4 - 0x2C0]; int x2D4; };
extern char D_00475480[];
void func_0023C660(struct S *p);
void func_00286630(struct S *p, int k);
void func_00286B00(struct S *p, int k);
void func_00286360(struct S *p, int k);
int func_001A7A80(struct O *o, int mask, float g);
void *func_002459F8(int k);
void func_00244F08(void *p, int k);
void *func_001F4A80(struct S *p);
void func_00168670(void *p, int k);
void func_00287448(struct S *p);
void func_002872B0(struct S *p);
void func_001F4B00(void *pg, int a, int b);
void func_002876E8(struct S *p);
void func_00285C98(struct S *p);
void func_00286250(struct S *p);
void func_00287620(struct S *p);
void func_002859F0(struct S *p)
{
    int old;
    func_0023C660(p);
    do {
        old = p->x190;
        switch (old) {
        case 2:
            if (p->x198 == 1)
                func_00286630(p, 0);
            if (p->x1A0 == 1)
                func_00286B00(p, 0);
            if (p->x198 == 0 && p->x1A0 == 0)
                func_00286360(p, 0);
            break;
        case 1:
            if (func_001A7A80(p->x134, 0x200, 0.15f)) {
                func_00244F08(func_002459F8(0x2A), 0);
                func_00168670(func_001F4A80(p), 0);
            }
            if (func_001A7A80(p->x134, 0x20, 0.15f))
                func_00287448(p);
            if (p->x198 == 1) {
                if (p->x2D4 && (p->x134->x18 & 8))
                    func_002872B0(p);
                if (p->x2BC && p->x1A0 == 1 && func_001A7A80(p->x134, p->x2B8, 0.15f))
                    func_001F4B00(D_00475480, p->x130, p->x1AC);
            }
            break;
        }
    } while (p->x190 != old);
    switch (p->x190) {
    case 0:
    case 1:
    case 2:
        func_002876E8(p);
        func_00285C98(p);
        func_00286250(p);
        func_00287620(p);
        break;
    }
}
