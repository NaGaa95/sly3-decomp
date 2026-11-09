// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Expanding-radius plane query: collects the tree entries within `radius` of `pos` (func_00119C20), casts a segment from
// `pos` along each new polygon's plane normal (scaled by radius + 1) and keeps the farthest hit as the result (hit point,
// normalized cast direction turned into a plane by func_00119EA8, kind 12). The radius doubles until a hit is found or
// it reaches 52000. `pos` is a plain parameter: it lives in its stack slot across the calls, so every use reloads it
// (the cast start is copied from the a3 argument reload, as in the original).
typedef int qword __attribute__((mode(TI)));
struct FRAME {};
struct REQ { unsigned int bytes, alignment; };
struct POLY { qword plane; char opaque10[8]; int flags; };
struct ENTRY { ENTRY *child[2]; POLY *poly; };
struct HIT { qword p; char pad10[0x30]; float time; char pad44[0x1C]; };
struct OUT { qword p, plane; int kind; };
union U { qword q; float f[4]; };
union SCR { REQ req; U u; };
struct WORK { FRAME frame; SCR scratch; HIT hits[16]; int count; ENTRY *end; };
extern "C" {
FRAME *func_001D2770(FRAME *);
void func_001D2798(FRAME *, int);
void *func_001D25B0(REQ *);
int func_00119C20(ENTRY *, void *, qword, float, int *, ENTRY **);
int func_00119BE8(ENTRY *, int, qword, qword, int, HIT *);
void func_00119EA8(qword *, qword, qword);
}
static inline float Max(float a, float b) { float r; __asm__("max.s %0,%1,%2" : "=f"(r) : "f"(a), "f"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword ScalarBits(float value) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(value)); return q; }
static inline qword AddScaled(qword position, qword plane, qword factor)
{
    qword r;
    __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(position), "j"(plane), "j"(factor));
    return r;
}
static inline qword Normal(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "0"(d));
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
extern "C" void func_001CCDD8(float sRadius, ENTRY *absp, void *pbspLimit, void *pgeom, qword pos, OUT *pcontact)
{
    WORK work;
    float radius = Max(sRadius, 100.0f);
    func_001D2770(&work.frame);
    ENTRY *first;
    {
        REQ *r = &work.scratch.req;
        r->bytes = 0xFFFC;
        r->alignment = 16;
        first = (ENTRY *)func_001D25B0(r);
    }
    int limit = 0x1555;
    if (radius < 52000.0f)
        do {
            work.end = first;
            work.count = limit;
            int status = func_00119C20(absp, pbspLimit, pos, radius, &work.count, &work.end);
            if (status < 0)
                goto more;
            if (status < 2)
                goto more;
            if (status != 2)
                goto more;
            {
                work.count = work.end - first;
                float best = 0.0f;
                int i;
                for (i = 0; i < work.count; i++) {
                    POLY *poly = first[i].poly;
                    if (poly->flags & 0x1000)
                        continue;
                    poly->flags |= 0x1000;
                    qword factor = ScalarBits(radius + 1.0f);
                    work.scratch.u.q = factor;
                    qword endpoint = AddScaled(pos, poly->plane, factor);
                    int found = func_00119BE8(work.end - 1, 0x7FFFFFFF, endpoint, pos, 16, work.hits);
                    if (found > 0) {
                        if (work.hits[0].time > best) {
                            best = work.hits[0].time;
                            qword normal = Normal(Sub(endpoint, pos));
                            pcontact->p = work.hits[0].p;
                            func_00119EA8(&pcontact->plane, normal, work.hits[0].p);
                            pcontact->kind = 12;
                        }
                    }
                }
                for (int j = 0; j < work.count; j++)
                    first[j].poly->flags &= ~0x1000;
                if (best > 0.0f) {
                    func_001D2798(&work.frame, 2);
                    return;
                }
            }
        more:
            radius += radius;
        } while (radius < 52000.0f);
    func_001D2798(&work.frame, 2);
}
