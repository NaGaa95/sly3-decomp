// Reference algorithm: src/hand/func_0012DE58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct R { char pad[0x1C]; float g; qword v; qword w; } R;
R *func_0012FFB0(int k, void *a, void *b, void *c, int d);
void func_0028ECE0(void *a, void *b, void *p);
R *func_00130348(void *a, void *b, void *c, float g, qword v, qword w)
{
    R *p = func_0012FFB0(8, a, b, c, 0x12);
    p->g = g;
    p->v = v;
    p->w = w;
    func_0028ECE0(a, b, p);
    return p;
}
