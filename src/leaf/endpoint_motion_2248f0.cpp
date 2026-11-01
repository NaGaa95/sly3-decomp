// Restart the motion of every path-following endpoint: place the cursor at its start fraction and pick the current segment and the time already spent in it (reversed profiles run the segments backwards). Sly 2 had this folded into the endpoint build function.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
struct PATH;
struct PARAMS { float fraction, speed, duration; int mode; };
struct SEGMENT { float start, speed, accel, duration, elapsed; };
struct MOTION { int count; SEGMENT segments[6]; int current; };
struct TRACK { PATH *path; float cursor; PARAMS params; MOTION motion; };
struct ENDPOINT {
    int id, kind;
    int pad8[2];
    union { qword point; TRACK track; };
};
struct ENTRY { ENDPOINT endpoints[2]; char pad160[0x170 - 0x160]; };
struct P {
    char pad0[0x178];
    int count;
    ENTRY *entries;
};
extern "C" float func_0022DFD8(PATH *);

extern "C" void func_002248F0(P *p)
{
    int i;
    for (i = 0; i < p->count; i++) {
        ENTRY *entry = &p->entries[i];
        uint j;
        for (j = 0; j < 2; j++) {
            ENDPOINT *endpoint = &entry->endpoints[j];
            switch (endpoint->kind) {
            case 0:
                break;
            case 1: {
                PARAMS *params = &endpoint->track.params;
                int reverse = endpoint->track.motion.segments[0].speed < 0.0f;
                float length = func_0022DFD8(endpoint->track.path);
                float fraction = params->fraction;
                endpoint->track.cursor = fraction * length;
                SEGMENT *seg;
                switch (params->mode) {
                case 0:
                    seg = endpoint->track.motion.segments;
                    if (reverse) seg->elapsed = (1.0f - fraction) * params->duration;
                    else seg->elapsed = fraction * params->duration;
                    endpoint->track.motion.segments[1].elapsed = 0.0f;
                    endpoint->track.motion.current = 0;
                    break;
                case 8:
                    seg = endpoint->track.motion.segments;
                    if (reverse) seg->elapsed = (1.0f - fraction) * params->duration;
                    else seg->elapsed = fraction * params->duration;
                    endpoint->track.motion.current = 0;
                    break;
                case 16:
                    for (endpoint->track.motion.current = 0; endpoint->track.motion.current < 3; endpoint->track.motion.current++) {
                        seg = &endpoint->track.motion.segments[endpoint->track.motion.current];
                        SEGMENT *next = seg + 1;
                        if (endpoint->track.cursor < next->start) {
                            float t = ((endpoint->track.cursor - seg->start) + (endpoint->track.cursor - seg->start)) / (seg->speed + next->speed);
                            if (reverse) {
                                int k = 5 - endpoint->track.motion.current;
                                endpoint->track.motion.current = k;
                                seg = &endpoint->track.motion.segments[k];
                                seg->elapsed = seg->duration - t;
                            } else {
                                seg->elapsed = t;
                            }
                            break;
                        }
                    }
                    break;
                }
                break;
            }
            }
        }
    }
}
