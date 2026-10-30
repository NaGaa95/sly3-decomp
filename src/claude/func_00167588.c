// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// NEEDS symbol D_00344840 = 0x00344840 (.data float -25.0) -> then LINKED_MATCH.
// Sly 2 reference: /home/claude/decomp src/hand/func_0014F040.c.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct PL { qword pos; qword plane; };
struct P { char pad[0x140]; float g140; };
struct SMP { float a[3]; };
extern float D_0034483C; /* 125.0f */
extern float D_00344840; /* -25.0f; NOT in symbol_addrs yet */
static const struct SMP s_smp = { { 2500.0f, 0.0f, 0.25f } };
extern float D_0036BBA8;
void *func_002BA000(void *p);
void func_0011E598(float g, float gTarget, float dt, const struct SMP *pv, float *pr);
static __inline__ float GDistPlane(qword plane, qword pos)
{
    U d, one;
    qword td, tone;
    float dist;
    func_002BA000(&d);
    func_002BA000(&one);
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w" : "=&j"(td), "=&j"(tone) : "j"(plane), "j"(pos));
    /* as in the Sly 2 match: "r,j"(td) with the never-chosen alternative forced off by "i,r"(0) (allocation only) */
    __asm__("mtc1 %1, %0" : "=f,f"(dist) : "r,j"(td), "i,r"(0));
    one.q = tone;
    d.q = td;
    return dist;
}
static __inline__ float GDot(const qword *pa, qword b)
{
    qword a = *pa;
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ float GMin(float a, float b) { return b < a ? b : a; }

float func_00167588(struct P *p, int unused, qword vIn, struct PL *pl)
{
    float r;
    qword plane = pl->plane;
    qword pos = pl->pos;
    func_0011E598(GDistPlane(plane, pos), GMin(p->g140 - D_0034483C, D_00344840), D_0036BBA8, &s_smp, &r);
    return GDot(&vIn, pl->plane) - r;
}
