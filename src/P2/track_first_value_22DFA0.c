// SLY3_CFLAGS: -Os -G0
struct FloatTrack { char prefix[0xD8]; int count; float *values; };
float func_0022DFA0(struct FloatTrack *track)
{
    return track->values[0];
}
