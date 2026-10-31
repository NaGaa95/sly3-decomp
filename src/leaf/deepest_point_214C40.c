// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Of all points, find the one that sits deepest inside the planes: for each point take its largest signed plane distance
// (stopping at the first plane in front of it), then keep the point with the smallest of those that is below zero.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern float D_00325BB8;
void *func_002BA000(void *p);
static __inline__ float GDistPlane(qword plane, qword pos)
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
    return dist;
}
void func_00214C40(int pointCount, qword *points, int planeCount, qword *planes, float *outDepth, qword *outPoint, qword *outPlane)
{
    float best = 0.0f;
    qword bestPoint, bestPlane;
    int i, j;
    for (i = 0; i < pointCount; i++) {
        qword point = points[i];
        qword plane, hitPlane;
        float distance = D_00325BB8;
        j = 0;
        if (j < planeCount) {
            do {
                float d;
                plane = planes[j];
                d = GDistPlane(plane, point);
                if (distance < d) {
                    distance = d;
                    hitPlane = plane;
                    if (distance >= 0.0f)
                        break;
                }
                j++;
            } while (j < planeCount);
        }
        if (distance < best) {
            best = distance;
            bestPlane = hitPlane;
            bestPoint = point;
        }
    }
    *outDepth = best;
    *outPoint = bestPoint;
    *outPlane = bestPlane;
}
