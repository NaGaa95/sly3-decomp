// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
struct VTE { short delta; short pad; int (*pfn)(void *); };
struct OBJ;
struct LIST { struct OBJ *pobj; int pad4; int *a8; int *aC; };
struct OBJ { struct VTE *pvt; };
struct BANK { unsigned char pad[0x50]; struct LIST list; };
struct ACT { unsigned char pad[0x218]; int n218; unsigned char pad21C[0x1454 - 0x21C]; int n1454; };
struct PLAYER {
    unsigned char pad[0x2F0]; int n2F0;
    unsigned char pad2F4[0x10D0 - 0x2F4]; void *p10D0;
    unsigned char pad10D4[0x11BC - 0x10D4]; int n11BC; int n11C0; float g11C4;
};
struct Self { unsigned char pad[0x10]; struct PLAYER *pplayer; unsigned char pad14[0x30 - 0x14]; int n30; struct ACT *p34; };
struct OUT { int kind; struct ACT *pact; float g; };
struct PAIR { int kind; struct ACT *pact; };
struct STAMP { int pad[3]; float t; };
extern struct CLOCK { float t; } g_clock;
extern unsigned char D_00474FF0[];
extern struct { unsigned char pad[0x4FB0]; struct BANK *pbank; } D_00475480;
/* 0x0047A430 has no symbol of its own; reach it through the preceding D_0047A424 object. */
extern struct { unsigned char pad[0xC]; int n; } D_0047A424;
struct PAIR func_00253EE8(struct PLAYER *p);
float func_00254640(struct PLAYER *p);
int func_0013B500(void *p, int k);
int func_00248858(void *p, int n);
int func_001A9478(void *p, int n);
struct STAMP *func_00170528(void *p, struct ACT *pact);
void *func_002485D8(void *p, int n, int f, struct PLAYER *pplayer);
void func_00244F08(void *p, struct PLAYER *pplayer);
}
static inline int Pick(int *aT, int *aF, int f, int i) { return (!f ? aF : aT)[i]; }
static inline int Pick2(struct LIST *pl, int f, int i) { int *a = !f ? pl->aC : pl->a8; return a[i]; }
extern "C" int func_0019AF98(struct Self *p, struct OUT *out)
{
    int f = 0;
    struct PAIR r = func_00253EE8(p->pplayer);
    switch (r.kind) {
    case -1:
        break;
    case 3:
        out->kind = 0x10;
        f = 1;
        out->pact = r.pact;
        out->g = func_00254640(p->pplayer);
        break;
    case 2:
        if (p->n30 != 4 || p->p34 != r.pact) {
            out->kind = 3;
            f = 1;
            out->pact = r.pact;
        }
        break;
    case 0:
        if (p->pplayer->n11BC && func_0013B500(r.pact, 0x33) &&
            g_clock.t - p->pplayer->g11C4 > 5.0f && !p->pplayer->n11C0 &&
            !func_00248858(D_00474FF0, -1) && !func_001A9478(&D_00475480, -1)) {
            struct ACT *pact = r.pact;
            struct STAMP *ps = func_00170528(p->pplayer->p10D0, pact);
            if (!pact->n1454 && g_clock.t - ps->t < 0.5f) {
                struct LIST *pl = &D_00475480.pbank->list;
                struct OBJ *pobj = pl->pobj;
                if (pobj) {
                    int i = pobj->pvt[1].pfn((char *)pobj + pobj->pvt[1].delta);
                    int ai = !p->pplayer->n2F0 ? pl->aC[i] : pl->a8[i];
                    func_00244F08(func_002485D8(D_00474FF0, ai, 1, p->pplayer), p->pplayer);
                    { float t = g_clock.t; p->pplayer->g11C4 = t; }
                }
            }
        }
        break;
    case 1:
        if (!r.pact->n1454 && r.pact->n218 && D_0047A424.n) {
            out->pact = r.pact;
            out->kind = 0x17;
            f = 1;
        }
        break;
    }
    return f;
}

