// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct F { char pad[8]; float g8; };
struct X { char pad[0x134]; struct F *pf; };
struct P { char pad[0x10]; struct X *px; char pad1[0xCC - 0x14]; int xCC; char pad2[0xD8 - 0xD0]; int state; float gDC;
    char pad3[0xEC - 0xE0]; int xEC; };
void func_00133510(struct P *p, int n);
void func_00133388(struct P *p)
{
    struct F *pf;
    int state;
    switch (p->xCC) {
    case 3: case 4: case 5: case 6: case 8: case 9:
        pf = p->px->pf;
        do {
            state = p->state;
            switch (state) {
            case 0:
                if (0.9f < pf->g8)
                    func_00133510(p, 1);
                else if (0.07f < g_clock.t - p->gDC)
                    p->xEC = 1;
                break;
            case 1:
                if (pf->g8 < 0.9f) {
                    if (g_clock.t - p->gDC < 0.3f)
                        p->xEC = 1;
                    func_00133510(p, 2);
                }
                break;
            case 3:
                if (0.2f < pf->g8)
                    p->xEC = 1;
                break;
            }
        } while (state != p->state);
    }
}
