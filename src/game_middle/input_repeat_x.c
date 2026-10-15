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
int func_001A99E0(struct JOY *p) {
    float g;
    if (!p->dirX) {
        int grf = func_001A7A80(p->input,0xA000,0.0f);
        if (grf & 0x8000) p->dirX = -1;
        else if (grf & 0x2000) p->dirX = 1;
        else if (p->input->gMag >= 0.8f && __builtin_fabsf(p->input->gX) > __builtin_fabsf(p->input->gY)) {
            if (p->input->gX < 0.0f) p->dirX = -1;
            else p->dirX = 1;
        }
        if (p->dirX) {
            g = 0.3333f;
            p->tRepX = g;
            p->tNextX = D_0036BB98.g40 + g;
        }
    }
    else {
        int fHeld = 0;
        if (p->dirX < 0) {
            if (p->input->grfHeld & 0x8000) fHeld = 1;
            else if (p->input->gMag >= 0.25f && __builtin_fabsf(p->input->gX) > __builtin_fabsf(p->input->gY) && p->input->gX < 0.0f) fHeld = 1;
        }
        else {
            if (p->input->grfHeld & 0x2000) fHeld = 1;
            else if (p->input->gMag >= 0.25f && __builtin_fabsf(p->input->gX) > __builtin_fabsf(p->input->gY) && 0.0f < p->input->gX) fHeld = 1;
        }
        if (!fHeld) {
            p->dirX = 0;
        }
        else if (p->tNextX <= D_0036BB98.g40) {
            g = GClamp(2.0f * p->tRepX / 3.0f, 0.1f, 0.3333f);
            p->tRepX = g;
            p->tNextX = D_0036BB98.g40 + g;
        }
        else {
            return 0;
        }
    }
    return p->dirX;
}
