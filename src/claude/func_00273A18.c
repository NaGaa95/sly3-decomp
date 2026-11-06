// Port of Sly 2 func_00220D40.
struct S { int a; float b; int c[2]; float d; int e[3]; float f; int g[3]; float h; char pad[0x54]; float i, j; };
extern float D_003290A0, D_003290A4;
extern char D_003290E8[];
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
float func_002A3EE8(float y, float x);
float func_0011EE68(void *p, float f);
void func_00273A18(struct S *p)
{
    if (p->i == D_003290A0 && p->j == D_003290A4) {
        float a = p->b + p->d;
        float f = func_002A3EE8(p->h, sqrtf_(a * a + p->f * p->f));
        f = func_0011EE68(D_003290E8, f);
        p->j = f;
        p->i = f;
    }
}
