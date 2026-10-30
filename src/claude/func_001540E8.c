// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *pfn; };
struct SLOT { int id; int x4; float t; };
struct DESC { int x0; int x4; int x8; int xC; char pad[0x3C - 0x10]; };
struct H { char pad[0x18]; int x18; char pad1[0x2C - 0x1C]; struct VTE *pvt; };
struct P { char pad[0xC]; struct VTE *pvt; char pad1[0x134 - 0x10]; struct H *p134; char pad2[0x11C4 - 0x138]; int x11C4; char pad3[0x1250 - 0x11C8]; struct SLOT aslot[3]; };
extern int D_00349040[];
extern struct DESC D_00343098[];
int func_001F4430(struct P *p);
void func_001540A0(void);
void func_00154350(struct P *p, struct SLOT *ps, int n);

#define HCALL(h, i) ((char *)(h) + (h)->pvt[i].d)
void func_001540E8(struct P *p)
{
    int i, f;
    if (!p->p134)
        return;
    for (i = 0; i < 3; i++) {
        int mask = D_00349040[i];
        struct SLOT *ps = &p->aslot[i];
        int id = ps->id;
        if (id == -1 || id == 0)
            continue;
        switch (ps->x4) {
        case 0:
            if (((int (*)(void *, int, float))p->p134->pvt[1].pfn)(HCALL(p->p134, 1), mask, 0.15f)) {
                f = 0;
                if ((func_001F4430(p) <= 0 && D_00343098[id].xC > 0) || ((id == 0x20 || id == 0x22) && p->x11C4 == 4))
                    f = 1;
                else if (id == 0x1A)
                    f = p->x11C4 != 4;
                if (f) {
                    ((void (*)(void *, int))p->p134->pvt[2].pfn)(HCALL(p->p134, 2), mask);
                    func_001540A0();
                } else if (((int (*)(void *, int))p->pvt[113].pfn)((char *)p + p->pvt[113].d, id)) {
                    ((void (*)(void *, int))p->p134->pvt[2].pfn)(HCALL(p->p134, 2), mask);
                    func_00154350(p, ps, D_00343098[id].x0);
                }
            }
            break;
        case 1:
            if (!(p->p134->x18 & mask) || !((int (*)(void *, int))p->pvt[113].pfn)((char *)p + p->pvt[113].d, id))
                func_00154350(p, ps, 0);
            else
                ((void (*)(void *, struct SLOT *))p->pvt[115].pfn)((char *)p + p->pvt[115].d, ps);
            break;
        }
    }
}
