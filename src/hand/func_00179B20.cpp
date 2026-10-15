// Sly 2 reference: src/hand/func_0015BD20.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
class CFrame {
    int m_a[4];
public:
    CFrame();
    ~CFrame();
};
#include "particle_emission_api.h"
struct LOC { ParticleWord *q0, *q1; float *q2, *q3; int f; int pad[3]; };
struct L2 { ParticleWord *a; ParticleWord *b; int pad[6]; };
struct B { int pad; int k4; char pad2[0xC4 - 8]; int kC4; };
extern "C" {
void func_001795F8(int a, B *b, LOC *ploc) __asm__("func_001795F8");

void func_00179800(int a, B *b, LOC *ploc, L2 *pl2) __asm__("func_00179800");
void func_00179228(B *b, void *c, int a, ParticleWord *q0, ParticleWord *q1, float *q2, float *q3, ParticleWord *x, ParticleWord *y) __asm__("func_00179228");
void func_00179B20(int a, B *b, void *c) __asm__("func_00179B20");
void func_00179B20(int a, B *b, void *c)
{
    if (a) {
        LOC loc;
        CFrame frame;
        loc.f = 1;
        func_001795F8(a, b, &loc);
        if (b->k4 == 1) {
            func_00178F80(b, c, a, loc.q0, loc.q1, loc.q2, loc.q3);
        } else {
            L2 l2;
            if (b->kC4 == 2) {
                func_00179800(a, b, &loc, &l2);
            } else {
                l2.a = 0;
                l2.b = 0;
            }
            func_00179228(b, c, a, loc.q0, loc.q1, loc.q2, loc.q3, l2.a, l2.b);
        }
    }
}
}
