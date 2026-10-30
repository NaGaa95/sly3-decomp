// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct S { int x0; void *p4; int state; float tState; float t10; void *p14; float g18; float g1C; float g20; float g24; };
int func_00162060(struct S *p);
int func_00161DF8(struct S *p, float a, float b);
void func_00162698(struct S *p, int state);
void func_00162148(struct S *p)
{
    int state;
    do {
        state = p->state;
        switch (state) {
        case -1:
            break;
        case 0:
            if (func_00162060(p) && func_00161DF8(p, 5.0f, p->g18))
                func_00162698(p, 1);
            break;
        case 1:
            if (func_00162060(p)) {
                if (g_clock.t - p->t10 > p->g24)
                    func_00162698(p, 0);
                else if (g_clock.t - p->tState > p->g20)
                    func_00162698(p, 2);
            } else {
                func_00162698(p, 0);
            }
            break;
        case 2:
            if (!func_00162060(p))
                func_00162698(p, 0);
            else if (g_clock.t - p->t10 > p->g24)
                func_00162698(p, 0);
            break;
        }
    } while (p->state != state);
    switch (p->state) {
    case 1:
    case 2:
        if (func_00161DF8(p, 50.0f, p->g1C))
            p->t10 = g_clock.t;
        break;
    }

}
