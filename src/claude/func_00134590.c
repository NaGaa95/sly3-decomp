// SLY3_CFLAGS: -Os -G0
/* per-frame update of a 6-state sequence: advance the 4-phase counter, then step the state machine until it settles */
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct P { char pad[0x10]; void *p10; char pad2[0x30 - 0x14]; int state; int pad34; int x38; float g3C; int pad40; int phase; };
void func_002389A0(struct P *p);
int func_001349C8(struct P *p);
void func_00134C48(struct P *p);
void func_001352F8(struct P *p);
int func_00238AD0(struct P *p);
void func_00134860(struct P *p, int state);
void func_0024E920(void *pv, int n);
void func_00134590(struct P *p)
{
    int state;
    func_002389A0(p);
    if (p->phase == 3 && !func_001349C8(p))
        p->g3C = g_clock.t;
    func_00134C48(p);
    p->phase = (p->phase + 1) % 4;
    func_001352F8(p);
    do {
        state = p->state;
        switch (state) {
        case 0:
            if (func_00238AD0(p))
                func_00134860(p, 1);
            break;
        case 1:
            if (0.5f < g_clock.t - p->g3C)
                func_00134860(p, 5);
            else if (func_00238AD0(p))
                func_00134860(p, 2);
            break;
        case 2:
            if (0.5f < g_clock.t - p->g3C)
                func_00134860(p, 5);
            else if (func_00238AD0(p))
                func_00134860(p, 3);
            break;
        case 3:
            if (func_00238AD0(p))
                func_00134860(p, 4);
            break;
        case 4:
        case 5:
            if (func_00238AD0(p))
                func_00134860(p, -1);
            break;
        }
    } while (p->state != state);
    func_0024E920(p->p10, p->x38);
}
/* The unit's next .rodata object (used by later functions); defined here so the jump table's rodata block places. */
const int D_0031F828[6] = { 0x11, 0x38, 0x26, 3, 4, 0x13 };
