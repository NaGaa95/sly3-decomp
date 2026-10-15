// Sly 2 reference: src/hand/func_001FC2E0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x70]; float a[6]; char pad2[0x3BC - 0x88]; int fl; };
struct S;
extern struct S D_00341FF0;
float func_0011EE68(struct S *, float);
void func_00245320(struct P *, int, int);
void func_00246190(struct P *p, unsigned int k, float g)
{
    if (k < 6) {
        float f = func_0011EE68(&D_00341FF0, g);
        if ((int)(f * 1024.0f) != (int)(p->a[k] * 1024.0f)) {
            p->fl |= 1 << k;
            p->a[k] = f;
            func_00245320(p, 0x80, 0x80);
        }
    }
}
