// SLY3_CFLAGS: -Os -G0
struct VEC { float x, y, z; };
struct S { char pad[0x310]; struct VEC v310; char pad1[4]; int x320; float f324; float f328; float f32C; float f330; float f334; float f338;
           char pad2[0x35C - 0x33C]; float f35C; float f360; char pad3[0x3C0 - 0x364]; float f3C0; char pad4[4]; int a3C8[6]; int x3E0;
           char pad5[0x414 - 0x3E4]; float f414; };
extern char D_003292D0[];
void func_001F3B50(struct S *p);
void func_0027C830(struct S *p, unsigned int i, void *q, float g);
static inline void SetVec(struct VEC *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}
void func_00279DD8(struct S *p)
{
    unsigned int i;
    func_001F3B50(p);
    p->f32C = 1100.0f;
    p->f330 = 700.0f;
    p->f414 = 1000.0f;
    p->f338 = 1.5f;
    p->f334 = 0.8f;
    SetVec(&p->v310, 2500.0f, -1500.0f, 0.0f);
    p->f324 = 2500.0f;
    p->f3C0 = 100.0f;
    p->f328 = 3500.0f;
    p->f35C = 250.0f;
    p->f360 = 2000.0f;
    p->x320 = 0;
    p->a3C8[0] = -1;
    p->a3C8[1] = -1;
    p->a3C8[2] = -1;
    p->a3C8[3] = -1;
    p->a3C8[4] = -1;
    p->a3C8[5] = -1;
    p->x3E0 = -1;
    for (i = 0; i < 4; i++)
        func_0027C830(p, i, D_003292D0, 50.0f);
}
