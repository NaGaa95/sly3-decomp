// Sly 2 reference: src/hand/func_001FB1F8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0x10]; float g; };
struct S;
extern struct S D_00341FF0;
float func_0011EE68(struct S *, float);
void func_00245320(struct P *, int, int);
void func_00244E08(struct P *p, float x)
{
    float g = func_0011EE68(&D_00341FF0, x);
    if ((int)(g * 1024.0f) != (int)(p->g * 1024.0f)) {
        p->g = g;
        func_00245320(p, 0x10, 0x10);
    }
}
