// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct Y { int a[3]; struct VTE *vt; };
struct E { char pad[0xD0]; };
struct Q { char pad[0x208]; struct Y *x208; };
struct S { int a[3]; struct VTE *vt; char pad[0xD0 - 0x10]; int cE; struct E *aE;
           char pad2[0x130 - 0xD8]; int x130; int x134; int x138; char pad3[0x160 - 0x13C]; int x160; struct Q *x164; };
extern qword D_00317560;
void func_001C7A00(struct S *p, struct Q *q, int k);
void func_0023D938(struct S *p, qword v);
void func_0023D9D0(struct S *p, qword v);
void func_0023EBF8(struct S *p, int k);
void func_0023EC98(struct S *p, int k);
void func_0023B978(struct S *p, struct E *e);
void func_00287F48(struct S *p)
{
    int i;
    struct Y *y;
    struct VTE *e;
    char *self;
    register void *q __asm__("$5"); /* pin: result straight into the second argument */
    p->x160 = 0;
    p->x130 = 0;
    p->x134 = 0;
    p->x138 = 0;
    func_001C7A00(p, p->x164, 0x13);
    y = p->x164->x208;
    e = &p->vt[35];
    self = (char *)p + e->d;
    q = y->vt[36].pf((char *)y + y->vt[36].d);
    e->pf(self, q);
    func_0023D938(p, D_00317560);
    func_0023D9D0(p, D_00317560);
    func_0023EBF8(p, 0);
    func_0023EC98(p, 1);
    for (i = 0; i < p->cE; i++)
        func_0023B978(p, &p->aE[i]);
}
