// SLY3_CFLAGS: -Os -G0
// Evaluate a clamped quadratic track at a time: normalized time (or 1 for a zero duration), c0 + t*(c1 + t*c2) clamped to
// [low, high], then handed to the target object.
struct QuadraticTrack { float c0, c1, c2; float pad0C; float low, high; float duration; };
struct TrackHolder { unsigned char pad[8]; struct QuadraticTrack *track; };
struct Target { unsigned char pad[0x14]; void *object; };
void func_002263B0(void *object, float value);
static inline float Clamp(float value, float low, float high)
{
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
void func_0022A430(struct Target *self, struct TrackHolder *holder, float time)
{
    struct QuadraticTrack *track = holder->track;
    float t, value;
    if (track->duration == 0.0f)
        t = 1.0f;
    else
        t = Clamp(time / track->duration, 0.0f, 1.0f);
    value = track->c0 + t * (track->c1 + t * track->c2);
    func_002263B0(self->object, Clamp(value, track->low, track->high));
}
