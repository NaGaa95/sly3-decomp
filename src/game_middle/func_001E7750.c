// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct HIT { qword q; char pad[0x50]; } HIT;
typedef struct S { char pad[0xD4]; int fWrap; } S;
void func_0022E330(S *p, float t, qword *pv, int z);
float func_0022E058(S *p, float t);
float func_0022DFB0(S *p);
float func_0022DFD8(S *p);
int func_001E6830(void *p, qword a, qword b, int c, HIT *ahit);


// Steps along path s from parameter t in 50-unit steps (backwards unless fForward), wrapping or clamping at the path ends and
// stopping at the first step whose segment is hit (same routine as Sly 2 func_001BD560): returns -1 with the hit parameter/point,
// 3 when the whole path was walked.
int func_001E7750(void *p, S *s, int fForward, qword *pq, float *pt, float t)
{
    qword av[2];
    HIT ahit[2];
    float dt;
    int fWrapped;
    int c;

    func_0022E330(s, t, &av[1], 0);
    dt = -50.0f;
    if (fForward) dt = 50.0f;
    fWrapped = 0;
    for (;;) {
        av[0] = av[1];
        t += dt;
        if (t <= func_0022DFB0(s)) {
            if (fWrapped) break;
            fWrapped = 1;
            if (s->fWrap) t = func_0022E058(s, t);
            else t = func_0022DFB0(s);
        } else if (func_0022DFD8(s) <= t) {
            if (fWrapped) break;
            fWrapped = 1;
            if (s->fWrap) t = func_0022E058(s, t);
            else t = func_0022DFD8(s);
        }
        func_0022E330(s, t, &av[1], 0);
        c = func_001E6830(p, av[0], av[1], 2, ahit);
        if (c > 0) {
            if (pt) *pt = t;
            if (pq) *pq = (ahit - 1)[c].q;
            return -1;
        }
    }
    return 3;
}
