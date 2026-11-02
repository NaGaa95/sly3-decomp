// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce -fno-gcse
// func_0022F058: find the curve segment that contains a parameter value, starting from the cached segment index at +0x168.
// The value is wrapped by func_0022DFF0, the index walks forward or backward over the sorted parameter table until the value
// falls inside [parameters[segment], parameters[segment + 1]), then the offset into the segment and its length are returned
// through the optional pointers and the index is cached again.
// The result block is written in both arms: each arm's `lower` is then a block-local value that local allocation numbers before
// the global `wrapped`; the identical tails are merged afterwards by cross-jumping (the original's shared block at the tail).
struct CurveSegmentView {
    unsigned char prefix[0xD4];
    int wrap;
    int count;
    float *parameters;
    unsigned char gapE0[0x168 - 0xE0];
    int segment;
};
float func_0022DFF0(struct CurveSegmentView *curve, float parameter);
int func_0022F058(struct CurveSegmentView *curve, float parameter, float *offset, float *length)
{
    float *parameters;
    float lower;
    float wrapped;
    int segment;
    wrapped = func_0022DFF0(curve, parameter);
    segment = curve->segment;
    parameters = curve->parameters;
    if (parameters[segment] < wrapped) {
        while (segment < curve->count - 1 && !(wrapped < parameters[segment]))
            segment++;
        segment--;
        lower = curve->parameters[segment];
        if (offset)
            *offset = wrapped - lower;
        if (length)
            *length = curve->parameters[segment + 1] - lower;
        curve->segment = segment;
        return segment;
    } else {
        while (segment > 0 && !(parameters[segment] <= wrapped))
            segment--;
        lower = curve->parameters[segment];
        if (offset)
            *offset = wrapped - lower;
        if (length)
            *length = curve->parameters[segment + 1] - lower;
        curve->segment = segment;
        return segment;
    }
}
