// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct O { char pad[0x250]; int state; float tState; };
void func_0015C790(struct O *p);
void func_0015D8C8(struct O *p, int s);
void func_0015D810(struct O *p)
{
    func_0015C790(p);
    switch (p->state) {
    case 0:
        break;
    case 1:
        if (g_clock.t - p->tState > 0.05f)
            func_0015D8C8(p, 2);
        break;
    case 2:
        func_0015D8C8(p, 0);
        break;
    }

}
