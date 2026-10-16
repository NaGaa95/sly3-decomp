// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int PathDistanceWord __attribute__((mode(TI)));
struct PathDistanceMatrix { PathDistanceWord rows[4]; };
struct PathDistanceMethod {
    short adjustment,reserved;
    const struct PathDistanceMatrix *(*matrix)(void *);
};
struct PathDistanceSource {
    char unaccessed[0xC];
    struct PathDistanceMethod *methods;
};
struct PathDistanceControl {
    char unaccessed[0xD4];
    int unrestricted;
};
struct S;
float func_0022DFD8(struct S *control);
void func_0022EA88(void *control,PathDistanceWord fallback,const void *metric,
                   PathDistanceWord *position,PathDistanceWord *direction,
                   float *parameter,float *finalParameter);

static inline float LimitPathDistance(float value,float lower,float upper)
{
    if(value<lower)
        return lower;
    if(upper<value)
        return upper;
    return value;
}

void func_001F3720(struct PathDistanceControl *control,
                   struct PathDistanceSource *source,float *distance)
{
    struct PathDistanceMethod *method=&source->methods[36];
    const struct PathDistanceMatrix *matrix=method->matrix((char *)source+method->adjustment);

    func_0022EA88(control,matrix->rows[3],0,0,0,0,distance);
    if(control->unrestricted==0)
        *distance=LimitPathDistance(*distance,100.0f,func_0022DFD8((struct S *)control)-35.0f);
}
