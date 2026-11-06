// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct E { char pad[0xD0]; };
struct Q { char pad[0x208]; int x208; };
struct S { int a[3]; struct VTE *vt; char pad[0xD0 - 0x10]; int cE; struct E *aE;
           char pad2[0x130 - 0xD8]; int x130; int x134; int x138; char pad3[0x160 - 0x13C]; int x160; struct Q *x164; };
void func_0023B920(struct S *p, struct E *e);
void func_001C8FB0(struct S *p, int k);
void func_0023EBF8(struct S *p, int k);
void func_0023EC98(struct S *p, int k);
void func_00287E70(struct S *p, qword v)
{
    int i;
    p->x160 = 0;
    p->x130 = 0;
    p->x134 = 0;
    p->x138 = 0;
    p->vt[8].pf((char *)p + p->vt[8].d);
    for (i = 0; i < p->cE; i++)
        func_0023B920(p, &p->aE[i]);
    func_001C8FB0(p, p->x164->x208);
    func_0023EBF8(p, 0);
    func_0023EC98(p, 1);
    p->vt[40].pf((char *)p + p->vt[40].d, v);
}
