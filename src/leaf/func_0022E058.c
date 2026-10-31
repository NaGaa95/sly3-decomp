// SLY3_CFLAGS: -Os -G0
// Curve parameter wrap: with the wrap flag set, positions outside [0, last knot] are folded back with GModPositive.
struct WrapCurve { char prefix[0xD4]; int wraps; int count; int reserved; float *values; };
float GModPositive__Fff(float value, float limit);
float func_0022E058(struct WrapCurve *curve, float position)
{
    float last;
    if (!curve->wraps)
        return position;
    last = curve->values[curve->count - 1];
    if (position >= 0.0f && position <= last)
        return position;
    return GModPositive__Fff(position, last);
}
