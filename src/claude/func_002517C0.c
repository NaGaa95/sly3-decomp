// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cases 12/15: 30 s, 14/16: 10 s, 20: 5 s (Sly 2 counterpart src/hand/func_00207288.c).
// Cf. Sly 2 src/hand/func_00207288.c: leave the current state after a per-state timeout.
extern struct CLOCK { float t; float dt; } g_clock;
struct S { char pad[0x112C]; int k; float t; };
void func_002514D8(struct S *p, int n);
void func_002517C0(struct S *p)
{
    switch (p->k) {
    case 14:
    case 16:
        if (g_clock.t - p->t > 10.0f)
            func_002514D8(p, -1);
        break;
    case 12:
    case 15:
        if (g_clock.t - p->t > 30.0f)
            func_002514D8(p, -1);
        break;
    case 20:
        if (g_clock.t - p->t > 5.0f)
            func_002514D8(p, -1);
        break;
    }
}
/* The rest of this unit's .rodata (used by func_00251880 and later functions); defined here so the
   jump table's 16-byte-padded section matches. */
const int D_003273C8[3] __attribute__((aligned(8))) = { 0x31, 5, 7 };
const float D_003273D4 = -3.40282346639e+38f;
