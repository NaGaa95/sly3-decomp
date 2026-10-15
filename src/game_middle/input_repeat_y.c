// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Advance the directional repeat state using the original query and clock fields.
struct INPUT {
    float gX,gY,gMag;
    float rightX,rightY,rightMagnitude;
    unsigned int grfHeld;
    float leftTimes[2],rightTimes[2];
    void *vtable2C;
};
struct JOY {
    struct INPUT *input;
    int dirX,dirY;
    float tNextX,tRepX,tNextY,tRepY;
};
struct CLOCK {
    char pad[0x40];
    float g40;
};
extern struct CLOCK D_0036BB98;
#include "input_query_api.h"
static __inline__ float GClamp(float g, float lo, float hi) {
    if (g < lo) return lo;
    if (g > hi) return hi;
    return g;
}
int func_001A9C38(struct JOY *p) {
    float g;
    if (!p->dirY) {
        int grf = func_001A7A80(p->input,0x5000,0.0f);
        if (grf & 0x1000) p->dirY = -1;
        else if (grf & 0x4000) p->dirY = 1;
        else if (p->input->gMag >= 0.8f && __builtin_fabsf(p->input->gY) > __builtin_fabsf(p->input->gX)) {
            if (0.0f < p->input->gY) p->dirY = -1;
            else p->dirY = 1;
        }
        if (p->dirY) {
            g = 0.3333f;
            p->tRepY = g;
            p->tNextY = D_0036BB98.g40 + g;
        }
    }
    else {
        int fHeld = 0;
        if (p->dirY < 0) {
            if (p->input->grfHeld & 0x1000) fHeld = 1;
            else if (p->input->gMag >= 0.25f && __builtin_fabsf(p->input->gY) > __builtin_fabsf(p->input->gX) && 0.0f < p->input->gY) fHeld = 1;
        }
        else {
            if (p->input->grfHeld & 0x4000) fHeld = 1;
            else if (p->input->gMag >= 0.25f && __builtin_fabsf(p->input->gY) > __builtin_fabsf(p->input->gX) && p->input->gY < 0.0f) fHeld = 1;
        }
        if (!fHeld) {
            p->dirY = 0;
        }
        else if (p->tNextY <= D_0036BB98.g40) {
            g = GClamp(2.0f * p->tRepY / 3.0f, 0.1f, 0.3333f);
            p->tRepY = g;
            p->tNextY = D_0036BB98.g40 + g;
        }
        else {
            return 0;
        }
    }
    return p->dirY;
}
