// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int DistanceWord __attribute__((mode(TI)));
struct S;
struct DistanceClampControl {
    char unaccessed[0xD4];
    int unrestricted;
};
DistanceWord func_00250600(struct S *source);
float func_0022DFD8(struct S *control);
void func_0022EA88(void *control, DistanceWord point, const void *metric,
    DistanceWord *position, DistanceWord *direction, float *parameter, float *distance);

void func_001A0C28(struct DistanceClampControl *control, struct S *source, float *distance)
{
    DistanceWord position;
    func_0022EA88(control, func_00250600(source), 0, &position, 0, 0, distance);
    if (!control->unrestricted) {
        float upper = func_0022DFD8((struct S *)control) - 30.0f;
        float value = *distance;
        if (value < 30.0f) value = 30.0f;
        else if (upper < value) value = upper;
        *distance = value;
    }
}
