// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce -fno-gcse
// func_0022F198: sibling of func_0022F058 for the curve variant whose parameter wrap is func_0022E058 (parameter table at +0xE0,
// count at +0xD8). Find the segment of the sorted parameter table that contains the wrapped value, starting from the cached
// index at +0x168, and return the offset into the segment and its length through the optional pointers.
// Each search arm starts from its own copy of the cached index, and the table is re-read for both results (the float stores
// may alias the view), so no shared `lower` exists.
struct CurveSegmentView {
    unsigned char prefix[0xD4];
    int wrap;
    int count;
    int reserved;
    float *parameters;
    unsigned char gapE4[0x168 - 0xE4];
    int segment;
};
float func_0022E058(struct CurveSegmentView *curve, float parameter);
int func_0022F198(struct CurveSegmentView *curve, float parameter, float *offset, float *length)
{
    float *parameters;
    float wrapped;
    int segment, start;
    wrapped = func_0022E058(curve, parameter);
    start = curve->segment;
    parameters = curve->parameters;
    if (parameters[start] < wrapped) {
        segment = start;
        while (segment < curve->count - 1 && !(wrapped < parameters[segment]))
            segment++;
        segment--;
    } else {
        segment = start;
        while (segment > 0 && !(parameters[segment] <= wrapped))
            segment--;
    }
    if (offset)
        *offset = wrapped - curve->parameters[segment];
    if (length)
        *length = curve->parameters[segment + 1] - curve->parameters[segment];
    curve->segment = segment;
    return segment;
}
