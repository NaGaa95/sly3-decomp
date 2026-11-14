// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0022E520: squared distance between the query point of a path search context and the path point at `parameter`. With a metric
// object (func_00244558) the difference vector is first mapped through it.
// Matching notes (reload spill register rotation):
//  * LengthSq lists the vector as TWO "j" inputs (`%2,%3`, as the Dot helpers do) and the final `mtc1` lists the squared length as an
//    allocation-only "j" input next to the "r" one (as src/claude/func_00120658.c). The two inputs keep the call result pseudo in the
//    VU class, so gcc reloads it into a VU spill register (vf4, the next one in the round robin after the vf3 temp of the difference);
//    the extra "j" use keeps the squared length a VU pseudo (vf1/vf2) whose qmfc2 is an ordinary input reload ($v0).
typedef int qword __attribute__((mode(TI)));
struct Metric;
struct Context { void *curve; struct Metric *metric; int reserved[2]; qword query; };
void func_0022E148(void *curve, float parameter, qword *position, void *direction);
qword func_00244558(struct Metric *metric, qword delta);
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float LengthSq(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v), "j"(v));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(d), "j"(d));
    return f;
}
float func_0022E520(struct Context *context, float parameter)
{
    qword position;
    func_0022E148(context->curve, parameter, &position, 0);
    if (context->metric)
        return LengthSq(func_00244558(context->metric, Sub(position, context->query)));
    return LengthSq(Sub(context->query, position));
}
