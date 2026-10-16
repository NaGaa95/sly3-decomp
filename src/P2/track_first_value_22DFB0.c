// SLY3_CFLAGS: -Os -G0
struct FloatTrack { char prefix[0xD8]; int count; int reserved; float *values; };
float func_0022DFB0(struct FloatTrack *track)
{
    return track->values[0];
}
