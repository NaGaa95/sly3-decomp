// Reference algorithm: src/hand/func_001E63C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0xD0]; int xE0; char pad1[0xF0 - 0xE4]; float *ag; char pad2[0x14C - 0xF4]; float agSub[11]; };
int func_0022F058(struct X *p, float *pa, float *pb);
void func_0022D950(struct X *p, int i);
static __inline__ float GLerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
float func_0022DD48(struct X *p)
{
    float a, b;
    float g;
    int i = func_0022F058(p, &a, &b);
    if (p->xE0 == 0) { g = GLerp(p->ag[i], p->ag[i + 1], a / b); } else { float u; int j; func_0022D950(p, i); u = a * 10.0f / b; j = (int)u; g = GLerp(p->agSub[j], p->agSub[j + 1], u - j); g += p->ag[i]; }
    return g;
}
