// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: src/hand/func_0014FEC8.c (local offset rotated by a yaw/pitch matrix, added to position).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { float f[4]; qword q; } U;
struct X { int a[9]; float g24; float g28; };
static const U s_offset = { { -50.0f, 0.0f, 0.0f, 0.0f } };
M3 func_0011CAE0(float x, float y);
qword func_00169FF0(struct X *p);
qword func_0016A078(struct X *p)
{
    M3 m;
    U v;
    qword pos;
    qword r2;
    v.q = s_offset.q;
    m = func_0011CAE0(p->g24, p->g28);
    pos = func_00169FF0(p);
    {
        qword r0 = m.r[0];
        qword r1 = m.r[1];
        register qword rv __asm__("vf4"); /* single pin: VU allocation order */
        r2 = m.r[2];
        rv = v.q;
        __asm__("vmulax.xyz $ACC, %1, %3x\n\tvmadday.xyz $ACC, %2, %3y\n\tvmaddz.xyz %0, %0, %3z"
                : "+j"(r2) : "j"(r0), "j"(r1), "j"(rv));
    }
    __asm__("vadd.xyzw %0, %0, %1" : "+j"(pos) : "j"(r2));
    return pos;
}
