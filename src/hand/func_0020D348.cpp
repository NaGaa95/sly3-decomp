// Sly 2 reference: src/hand/InitMatch__FP5MATCHP6VECTORfP2SO.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct SO;
struct MATCH { char pad[0x20]; float g20; float g24; int n28; int pad2; qword q30; };
extern qword D_00341FE0;
// The complete inherited initializer stores all128 input bits from A1 and reads F12.
// Its original body consumes no A2 input; the historical outer context is unused.
extern "C" void func_0020BC20(MATCH *p, qword position, float g) __asm__("func_0020BC20");
void InitMatch(MATCH *pmatch, qword position, float g, SO *pso) __asm__("func_0020D348");
void InitMatch(MATCH *pmatch, qword position, float g, SO *pso)
{
    (void)pso;
    func_0020BC20(pmatch, position, g);
    pmatch->q30 = D_00341FE0;
    pmatch->g20 = g;
    pmatch->g24 = 1.0f - g;
    pmatch->n28 = 0;
}
