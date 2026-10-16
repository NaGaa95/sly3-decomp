// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct S { char prefix[0xD0]; int mode; };
void func_0022E5B0(struct S *, QWORD, int, void *, void *, float *, float *, float);
void func_0022E938(struct S *, QWORD, int, void *, void *, float *, float *, float);
void func_0022EA50(struct S *object, QWORD value, int distanceKind, void *position, void *direction, float *progress, float *length, float initial)
{
    if (!object->mode) func_0022E5B0(object, value, distanceKind, position, direction, progress, length, initial);
    else func_0022E938(object, value, distanceKind, position, direction, progress, length, initial);
}
