// SLY3_CFLAGS: -Os -G0 -ffast-math
struct S { char pad[0x204]; char nav[1]; };
struct P { char pad[0x8]; void *x8; };
struct G { char pad[0x150]; float x150; float x154; };
struct PAD { char pad[0x24]; float x24; float x28; };
extern struct G D_00474FF0;
extern struct PAD D_0036DBE0;
extern char D_00341FF0[];
extern float D_0036BBDC;
extern float D_00345F24, D_00345F28;
int func_001A99E0(void *);
int func_001A9C38(void *);
float func_0011EE68(void *, float);
void func_00248A78(struct G *, int, float, int);
void func_00261580(void *, int, float);
void func_00196818(struct PAD *, float, float);
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }
void func_001D3B58(struct S *s, struct P *p, int *pk)
{
    switch (*pk) {
    case 0x77: {
        float f = (float)func_001A99E0(s->nav);
        float g;
        if (f == 0.0f)
            return;
        g = func_0011EE68(D_00341FF0, D_00474FF0.x154 + f * D_0036BBDC * 1.5f);
        func_00248A78(&D_00474FF0, 1, g, 1);
        func_00261580(p->x8, 0x37C, g);
        break;
    }
    case 0x78: {
        float f = (float)func_001A99E0(s->nav);
        float g;
        if (f == 0.0f)
            return;
        g = func_0011EE68(D_00341FF0, D_00474FF0.x150 + f * D_0036BBDC * 1.5f);
        func_00248A78(&D_00474FF0, 0, g, 1);
        func_00248A78(&D_00474FF0, 3, g, 1);
        func_00261580(p->x8, 0x37C, g);
        break;
    }
    case 0x4E: {
        void *nav = s->nav;
        float x = (float)func_001A99E0(nav);
        float y = (float)func_001A9C38(nav);
        float a, b;
        if (x == 0.0f && y == 0.0f)
            return;
        {
            float lim1 = 212.0f;
            a = GClamp(D_0036DBE0.x24 + x * D_00345F24, -lim1, lim1);
        }
        {
            int range = 200, steps = 5;
            int range2 = 200, steps2 = 5; /* separate locals per limit: the second division is CSEd, its li 5 stays (target) */
            b = GClamp(D_0036DBE0.x28 + y * D_00345F28, -(float)(range / steps), (float)(range2 / steps2));
        }
        func_00196818(&D_0036DBE0, a, b);
        break;
    }
    }
}
