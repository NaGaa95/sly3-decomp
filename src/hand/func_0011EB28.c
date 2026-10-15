// Range-reduce the angle and evaluate the original sine polynomial; derive cosine.
// A single EE FPU sqrt intrinsic preserves the target square-root instruction.
#include "m2c_prelude.h"
static inline f32 clamp_ee(f32 g, f32 lo, f32 hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
static inline f32 sqrt_ee(f32 x) { f32 r; __asm__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
void func_0011EB28(f32 *sine_out, f32 *cosine_out, f32 angle) {
    f32 phase;
    f32 squared_angle;
    f32 cosine;
    f32 term;
    f32 sine;
    s32 odd_turn;
    s32 turn;

    phase = (angle + 1.5707964f) * 0.31830987f;
    turn = (s32) phase;
    if (phase < 0.0f) {
        turn -= 1;
    }
    odd_turn = turn & 1;
    term = angle - ((f32) turn * 3.1415927f);
    if (odd_turn != 0) {
        term = -term;
    }
    squared_angle = term * term;
    sine = term;
    term *= squared_angle;
    sine += term * -0.16666657f;
    term *= squared_angle;
    sine += term * 0.0083330255f;
    term *= squared_angle;
    sine += term * -0.00019807414f;
    term *= squared_angle;
    sine += term * 0.000002601887f;
    sine = clamp_ee(sine, -1.0f, 1.0f);
    cosine = sqrt_ee(1.0f - (sine * sine));
    if (odd_turn != 0) {
        cosine = -cosine;
    }
    *cosine_out = cosine;
    *sine_out = sine;
}
