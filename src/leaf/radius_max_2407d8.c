// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
struct PointSet { int count; qword *points; };
float func_002407D8(struct PointSet *set)
{
    float largest=0.0f;
    int i;
    for(i=0;i<set->count;i++) {
        qword *point=set->points+i;
        qword value=*point,one;
        float squared;
        __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(value), "=&j"(one));
        __asm__("mtc1 %1,%0" : "=f"(squared) : "r"(value));
        if(largest<squared)
            largest=squared;
    }
    return sqrtf_(largest);
}
