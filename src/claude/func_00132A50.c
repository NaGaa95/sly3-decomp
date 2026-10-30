// SLY3_CFLAGS: -Os -G0
/* step a two-phase timer state machine (states 1 and 2 at xD0) until it settles */
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct X { char pad[0x218]; int x218; char pad2[0x4B0 - 0x21C]; char a4B0[4]; };
struct P { char pad[0x10]; struct X *px; char pad2[0x30 - 0x14]; int x30; char pad3[0xCC - 0x34]; int xCC; int state;
    float gD4; char pad4[0xE0 - 0xD8]; float gE0; float gE4; char pad5[0x100 - 0xE8]; int x100; };
void func_00132C58(struct P *p, int n);
void func_00132BC0(struct P *p);
void func_00259D50(void *pv);
void func_00132A50(struct P *p)
{
    int state;
    if (p->x30 == 1)
        func_00132C58(p, 4);
    do {
        state = p->state;
        switch (state) {
        case 1:
            if (p->px->x218 && (p->xCC == 6 || p->xCC == 8 || p->gD4 + 0.15f < g_clock.t))
                func_00132BC0(p);
            else if (p->gE4 <= g_clock.t)
                func_00132C58(p, 2);
            break;
        case 2: {
            struct X *px = p->px;
            if (px->x218 || 5.0f < g_clock.t - p->gE0)
                func_00132BC0(p);
            else if (p->gE0 <= g_clock.t) {
                if (p->xCC == 1)
                    func_00132C58(p, 3);
                else if (p->x100) {
                    p->x100 = 0;
                    func_00259D50(px->a4B0);
                }
            }
            break;
        }
        }
    } while (state != p->state);
}
