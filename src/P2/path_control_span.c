// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct CurvePresenceView { char prefix[0xD4]; int present; };
float func_0022DFB0(struct S *object);
float func_0022DFD8(struct S *object);

int func_001F3990(void *receiver, float *output)
{
    if (((struct CurvePresenceView *)receiver)->present) {
        output[0] = func_0022DFB0((struct S *)receiver);
        output[1] = func_0022DFD8((struct S *)receiver);
        return 1;
    }
    return 0;
}
