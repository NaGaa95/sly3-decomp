// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001E6BF0: tests a point against a convex volume (the cplane - 1 planes built by func_001E75F0);
// returns 0 as soon as the point is in front of a plane, else 1.
// Allocation notes: GDistPlane takes its operands through pointers. Taking the address of the point parameter makes
// purge_addressof renumber it above the loop-loaded plane, which gives the original spill slot order (plane 0x20, point 0x30).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct X { char pad[0xD8]; int cplane; char pad2[0x1DC - 0xDC]; qword *aplane; };
void func_001E75F0(struct X *p);
void func_002BA000(void *p);
static __inline__ float GDistPlane(const qword *plane, const qword *pos)
{
    U d, one;
    qword td, tone;
    float dist;
    func_002BA000(&d);
    func_002BA000(&one);
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w" : "=&j"(td), "=&j"(tone) : "j"(*plane), "j"(*pos));
    /* "r,j"(td) with the never-chosen alternative forced off by "i,r"(0): allocation only (as in src/claude/func_00167588.c) */
    __asm__("mtc1 %1, %0" : "=f,f"(dist) : "r,j"(td), "i,r"(0));
    one.q = tone;
    d.q = td;
    return dist;
}
int func_001E6BF0(struct X *p, qword pos)
{
    int i;
    func_001E75F0(p);
    for (i = 0; i < p->cplane - 1; i++) {
        qword plane = p->aplane[i];
        if (0.0f < GDistPlane(&plane, &pos))
            return 0;
    }
    return 1;
}
