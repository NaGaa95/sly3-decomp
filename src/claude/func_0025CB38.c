// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct PE { char pad[0x14]; float f14; };
struct O { char pad[0xEC]; struct PE *pEC; float fF0; };
struct ENT { struct O *o; float f4; int n8; };
struct P {
    char pad[0x42D8]; struct ENT a42D8[4]; char pad4308[0x4308 - 0x4308]; int c4308; struct O *a430C[1];
};
struct P2 { char pad[0x4F60]; float f4F60; int n4F64; };
struct CLOCK { float t, dt; };
extern struct CLOCK g_clock;
extern char D_00327730[];
int func_00261BD0(struct O *);
float func_0011E730(float gCur, float dgCur, float gTarget, float dt, void *psmpa, float *pdgNext);
void *func_002459F8(int id);
void func_00244F08(void *m, int n);
static __inline__ float GMax(float a, float b) { return a > b ? a : b; }
void func_0025CB38(struct P *p)
{
    int i, j;
    struct O *o;
    float x = 0.0f, y = x;
    for (i = 0; i < p->c4308; i++) {
        o = p->a430C[i];
        if (func_00261BD0(o)) {
            if (o->fF0 <= 0.0f) continue;
            y = o->fF0;
        }
    }
    for (j = 0; j < 4; j++) {
        struct ENT *e = &p->a42D8[j];
        o = e->o;
        if (!o || !func_00261BD0(o)) {
            e->n8 = 1;
            continue;
        }
        if (j > 0 && y != 0.0f) {
            x = y;
            y = 0.0f;
        }
        if (e->n8) {
            o->pEC->f14 = x;
            e->f4 = 0.0f;
            e->n8 = 0;
        } else {
            o->pEC->f14 = func_0011E730(o->pEC->f14, e->f4, x, g_clock.dt, D_00327730, &e->f4);
        }
        x += 65.0f;
        if (j == 3) {
            struct P2 *q = (struct P2 *)p;
            int n = (int)GMax(0.0f, q->f4F60 - g_clock.t);
            if (n != q->n4F64) {
                func_00244F08(func_002459F8((n & 1) ? 0x30 : 0x31), 0);
                q->n4F64 = n;
            }
        }
    }
}
