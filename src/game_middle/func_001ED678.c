// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Point query in the BSP of the world: walk the plane tree from the root down to a leaf and return the leaf's entry
// (or the default entry when the walk runs off the tree and the caller allows it). Based on Sly 2 func_001C0D70.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct N { qword *pplane; unsigned short ach[2]; };
struct B { int c; struct N *an; int x8, xc; int x10; int x14; void **al; };
struct G { char pad[0x4DF8]; void *x4DF8; struct B *pbsp; };
extern struct G D_00475480;
void func_002BA000(void *p);
static __inline__ int ISide(qword plane, qword pos)
{
    U d, one;
    qword td, tone;
    float dist;
    func_002BA000(&d);
    func_002BA000(&one);
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w" : "=&j"(td), "=&j"(tone) : "j"(plane), "j"(pos));
    __asm__("mtc1 %1, %0" : "=f,f"(dist) : "r,j"(td), "i,r"(0));
    one.q = tone;
    d.q = td;
    return 0.0f < dist;
}
void *func_001ED678(qword pos, int f)
{
    struct B *pb = D_00475480.pbsp;
    struct N *pn, *pnEnd, *an;
    void **al;
    unsigned int c;
    if (!pb)
        return 0;
    pn = pb->an;
    pnEnd = pn + pb->c;
    al = pb->al;
    an = pn;
    while (pn != pnEnd) {
        c = pn->ach[ISide(*pn->pplane, pos)];
        if (c & 0x8000) {
            c &= 0x7FFF;
            return al[c];
        }
        pn = &an[c];
    }
    if (f || !pb->x10)
        return D_00475480.x4DF8;
    return 0;
}
