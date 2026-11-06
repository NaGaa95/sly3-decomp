// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x9C]; float f9C; float fA0; };
extern char D_003295C0[], D_003295C8[];
int func_00271448();
float func_002A4188(float x, float y);
float func_0011ED10(float x);
void func_00283620(struct S *p, float g, void *o)
{
    float t;
    int m, s;
    if (p->fA0 != 0.0f) {
        func_00271448(o, D_003295C0, (int)(g * 1000.0f + 0.5f));
        return;
    }
    if (p->f9C == 0.0f)
        return;
    t = 1.0f;
    t -= g;
    t *= p->f9C;
    m = func_002A4188(t, 3600.0f) * 0.016666668f;
    s = func_002A4188(t, 60.0f);
    t -= func_0011ED10(t);
    t *= 100.0f;
    func_00271448(o, D_003295C8, m, s, (int)t);
}
