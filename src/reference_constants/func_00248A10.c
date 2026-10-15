#include "gain_control_api.h"
// Reference algorithm: src/hand/func_001FE9F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct P {
    char pad[0x1C0];
    float g;
};
struct S;
extern struct S D_00341FF0;
float func_0011EE68(struct S *, float);
void func_00290E98(int, int);
void func_00248A10(void *receiver, float x) {
    struct P *p = (struct P *)receiver;
    float g = func_0011EE68(&D_00341FF0, x);
    int n = (int)(g * 1024.0f);
    if ((int)(p->g * 1024.0f) != n) {
        p->g = g;
        func_00290E98(0x10, n);
    }
}
