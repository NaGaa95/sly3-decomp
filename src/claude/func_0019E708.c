// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Node { unsigned char pad0[0x2C]; float lo; float hi; float start; float end; unsigned char pad3C[8]; float pos; float dist; unsigned char pad4C[0x60 - 0x4C]; struct Node *next; };
struct Track { unsigned char pad0[0xC]; int count; struct Node *first; unsigned char pad14[0x20 - 0x14]; float spacing; void *path; float at; };
float func_0022DFD8(void *path);
static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) v = lo;
    else if (hi < v) v = hi;
    return v;
}
static inline float Min(float a, float b) { return a < b ? a : b; }
void func_0019E708(void *self, struct Track *track)
{
    float total = func_0022DFD8(track->path);
    float seg = Min(track->spacing, total * 0.5f / (float)track->count);
    struct Node *node;
    int i = 0;
    for (node = track->first; node; node = node->next, i++) {
        int k = track->count - i - 1;
        float u = Clamp((track->at - node->start) / (node->end - node->start), 0.0f, 1.0f);
        float v = (1.0f - u) * node->lo + u * node->hi;
        float lo = ((float)i * 2.0f + 1.0f) * seg;
        float hi = total - ((float)k * 2.0f + 1.0f) * seg;
        float x = v;
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        node->pos = x;
        x = (node->lo + node->hi) * 0.5f;
        node->dist = -__builtin_fabsf(x - track->at);
    }
}
