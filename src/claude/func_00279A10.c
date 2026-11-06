// SLY3_CFLAGS: -Os -G0
struct VEC { float x, y, z; };
struct VTE { short d; short pad; void *(*pf)(void *); };
struct O { int a[3]; struct VTE *vt; };
struct Q { char pad[0x48]; int x48; char pad2[0x284 - 0x4C]; void *x284; };
struct S { struct O *x0; char pad[0x1C]; struct Q *x20; char pad2[0xC]; struct VEC v30; };
extern struct { int x0; int x4; int x8; } D_0036DBE0;
void func_00169E28(struct S *p);
void func_00167AB0(struct O *p, int a, int b, int c, int d);
void func_0011D048(void *m, float *pan, float *tilt);
float func_0011E438(void *p, float g);
void func_0024E878(int x, float g);
static inline void SetVec(struct VEC *v, float x, float y, float z)
{
    v->z = z;
    v->y = y;
    v->x = x;
}
void func_00279A10(struct S *p)
{
    float a[2];
    void *m;
    float f;
    func_00169E28(p);
    func_00167AB0(p->x0, 0x60, 0, D_0036DBE0.x4, D_0036DBE0.x8);
    SetVec(&p->v30, 0.0f, 0.0f, 0.0f);
    m = p->x0->vt[36].pf((char *)p->x0 + p->x0->vt[36].d);
    func_0011D048(m, &a[0], &a[1]);
    f = func_0011E438(p->x20->x284, a[0]);
    func_0024E878(p->x20->x48, f);
}
