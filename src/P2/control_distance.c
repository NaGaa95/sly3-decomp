// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int DistanceWord __attribute__((mode(TI)));

struct S;
struct DistanceControl {
    char unaccessed[0xD4];
    int unrestricted;
};

DistanceWord func_00250600(struct S *source);
float func_0022DFD8(struct S *control);
void func_0022EA88(void *control,DistanceWord fallback,const void *metric,
                   DistanceWord *position,DistanceWord *direction,
                   float *parameter,float *finalParameter);

static inline float LimitDistance(float value,float lower,float upper)
{
    if(value<lower)
        return lower;
    if(upper<value)
        return upper;
    return value;
}

void func_00203818(struct DistanceControl *control,struct S *source,float *distance)
{
    DistanceWord position;

    func_0022EA88(control,func_00250600(source),0,&position,0,0,distance);
    if(control->unrestricted==0)
        *distance=LimitDistance(*distance,50.0f,func_0022DFD8((struct S *)control)-50.0f);
}
