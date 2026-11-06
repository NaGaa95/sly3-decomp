// SLY3_CFLAGS: -Os -G0
struct SMP;
extern struct SMP D_00329750;
extern struct { float dt; } D_0036BB9C;
struct S { char pad[0x1A8]; float f1A8; char pad2[0x2CC - 0x1AC]; int x2CC; };
int func_001F43C8(struct S *p);
float func_0011E598(struct SMP *psmp, float *pdgNext, float gCur, float gTarget, float dt);
void func_002875C0(struct S *p);
void func_00240DB0(struct S *p);
void func_00287620(struct S *p)
{
    if (p->x2CC != func_001F43C8(p)) {
        float cur = p->x2CC;
        float tgt = func_001F43C8(p);
        p->x2CC = func_0011E598(&D_00329750, 0, cur, tgt, D_0036BB9C.dt);
        func_002875C0(p);
    }
    if (p->f1A8 > 0.0f) {
        p->f1A8 = p->f1A8 - D_0036BB9C.dt;
        if (p->f1A8 <= 0.0f) {
            p->f1A8 = 0.0f;
            func_00240DB0(p);
        }
    }
}
