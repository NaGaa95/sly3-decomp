// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sweeps a moving box along the trajectory func_00118558 describes and reports whether the path is blocked:
// each step tests the segment from the previous sample, the optional end point *pc is probed when it is close
// to the sample (or at the last step), and the frame object brackets the query.
typedef int qword __attribute__((mode(TI)));
extern "C" {
void func_0025CF18(void *g, qword a, qword b, void *p1, void *p2, int *pi, int *pj);
struct HIT;
int func_00165000(int z, qword a, qword b, int i, int j, HIT *phit);
void func_00118558(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *ppos, int m, int n);
extern char D_00475480[];
}
class FRAME { public: FRAME(); ~FRAME(); };
struct HIT { qword pos; char pad[0x34]; float x44; char pad2[0x18]; };
struct BODY { char pad[0x1130]; float limit; };
struct ACTOR { BODY *body; };
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float GetXM(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    d = Sub(a, b);
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return GetXM(l);
}
extern "C" int func_001BB918(ACTOR *self, void *p1, void *p2, qword a, qword va, qword b, qword vb, qword *pc, float tMax)
{
    struct V { float x, y, z; } __attribute__((aligned(16))) pos;
    HIT hit;
    FRAME frame;
    int i, j;
    qword mn, mx, prev;
    float t;
    if (pc) {
        __asm__("vmax.xyz %0, %2, %3\n\tvmini.xyz %1, %2, %3" : "=&j"(mx), "=j"(mn) : "j"(b), "j"(*pc));
        __asm__("vmini.xyz %1, %2, %1\n\tvmax.xyz %0, %2, %0" : "+j"(mx), "+j"(mn) : "j"(a));
    } else {
        mn = a;
        mx = b;
    }
    func_0025CF18(D_00475480, mn, mx, p1, p2, &i, &j);
    for (t = 0.0f; ; t = t + 0.1f < tMax ? t + 0.1f : tMax) {
        func_00118558(tMax, t, 1.0f, a, va, b, vb, (qword *)&pos, 0, 0);
        if (t != 0.0f && func_00165000(0, prev, *(qword *)&pos, i, j, &hit)) {
            if (100.0f < Dist(hit.pos, b))
                return 1;
        }
        if (pc) {
            int probe = Dist(*pc, *(qword *)&pos) < self->body->limit || t == tMax;
            if (probe) {
                if (!func_00165000(0, b, *pc, i, j, &hit))
                    return 0;
                if (hit.x44 == 1.0f || Dist(hit.pos, *pc) < 50.0f)
                    return 0;
            }
        }
        prev = *(qword *)&pos;
        if (t == tMax)
            break;
    }
    if (pc)
        return 1;
    return 0;
}
