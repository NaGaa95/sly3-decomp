// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
// Insert a begin event (g0, kind 1) and an end event (g1, kind 0) into a time-sorted array of 8-byte events.
// Ported from Sly 2 func_001C1A38.
struct Event { float t; unsigned short kind; unsigned short bit; };
extern "C" void *func_00291F38(void *dst, const void *src, unsigned int cb);
static inline void Move(void *dst, void *src, unsigned cb) { func_00291F38(dst, src, cb); }
extern "C" void func_001EE2E8(int count, Event *events, int bit, float begin, float end)
{
    int i, j;
    for (i = 0; i < count; i++)
        if (begin <= events[i].t)
            break;
    for (j = i; j < count; j++)
        if (end < events[j].t)
            break;
    Move(&events[j + 2], &events[j], (count - j) * 8U);
    events[j + 1].t = end;
    events[j + 1].kind = 0;
    events[j + 1].bit = bit;
    Move(&events[i + 1], &events[i], (j - i) * 8U);
    events[i].bit = bit;
    events[i].t = begin;
    events[i].kind = 1;
}
