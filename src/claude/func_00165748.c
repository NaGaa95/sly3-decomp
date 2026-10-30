// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Camera setup (cameras 3/4/5). The two vectors are non-const statics (reloaded after every call in the target); they live at 0x320D40/0x320D50.
typedef int qword __attribute__((mode(TI)));
typedef union { float af[4]; qword q; } QF;
struct RC { int x0, y0, x1, y1; };
static QF s_posCm = { { 0.0f, -2000.0f, 500.0f, 0.0f } };
static QF s_posLook = { { 0.0f, 0.0f, 0.0f, 0.0f } };
static const struct RC s_rc1 = { 6, 3, 485, 236 };
static const struct RC s_rc2 = { 158, 242, 637, 474 };
struct LO;
struct VTE { short d; short pad; void (*pfn)(struct LO *); };
struct LOV { char pad[0x1C0]; struct VTE e; };
struct LO { int a[3]; struct LOV *pvt; };
struct CM;
struct W {
    char pad[0x305C]; int x305C; char pad1[0x3EB8 - 0x3060]; int x3EB8; char pad2[0x463C - 0x3EBC];
    struct LO *p463C; struct CM *p4640; struct CM *p4644;
};
int func_0011AF08(int *p);
void *func_00150690(int a, int b, int c, int d);
void func_00168478(void *pcm, int n);
void func_00166E48(void *pcm, qword a, qword b, float c, float d);
void func_001679E0(void *pcm, float g);
void func_00167A50(void *pcm, float g);
void func_00167BF0(void *pcm, int x0, int y0, int x1, int y1);
void func_00165748(struct W *p)
{
    struct CM *pcm1;
    struct CM *pcm2;
    if (func_0011AF08(&p->x305C) == 1) {
        p->p463C = (struct LO *)p->x305C;
    } else {
        p->p463C = func_00150690(5, 0, 3, -1);
        func_00168478(p->p463C, 0);
        func_00166E48(p->p463C, s_posCm.q, s_posLook.q, 0.0f, 0.0f);
    }
    pcm1 = func_00150690(5, 0, 4, -1);
    func_00166E48(pcm1, s_posCm.q, s_posLook.q, 0.0f, 0.0f);
    func_001679E0(pcm1, 70.0f);
    func_00167A50(pcm1, 100000.0f);
    func_00168478(pcm1, 0);
    func_00167BF0(pcm1, s_rc1.x0, s_rc1.y0, s_rc1.x1, s_rc1.y1);
    p->p4640 = pcm1;
    pcm2 = func_00150690(5, 0, 5, -1);
    func_00166E48(pcm2, s_posCm.q, s_posLook.q, 0.0f, 0.0f);
    func_001679E0(pcm2, 70.0f);
    func_00167A50(pcm2, 100000.0f);
    func_00168478(pcm2, 1);
    func_00167BF0(pcm2, s_rc2.x0, s_rc2.y0, s_rc2.x1, s_rc2.y1);
    p->p4644 = pcm2;
    if (p->x3EB8 == 0)
        p->p463C->pvt->e.pfn((struct LO *)((char *)p->p463C + p->p463C->pvt->e.d));
}
