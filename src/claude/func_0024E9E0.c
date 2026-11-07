// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; int (*pfn)(void *); };
struct VT { char pad[0x210]; struct VTE e210; };
struct LO { char pad[0xC]; struct VT *pvt; };
struct ENDPOINT { void *shape, *owner; struct LO *object; void *lo; qword pos; qword local; int pad[4]; };
struct XP { struct ENDPOINT ae[2]; qword normal; float distance; int pad94[2]; int kind; int padA0[3]; struct XP *next; };
struct BUCKET { struct XP *head; struct BUCKET *next; struct XP **ptail; };
struct WORLD { char pad[0x64]; struct BUCKET *pbucket; struct XP *head68; };
struct P {
    char pad[0xDC]; struct WORLD *pw; char padE0[0x218 - 0xE0]; struct XP *pxp218; float f21C;
    char pad220[0x240 - 0x220]; qword q240; char pad250[0x2E8 - 0x250]; struct LO *p2E8;
};
struct CLOCK { float t, dt; };
extern struct CLOCK g_clock;
extern char D_00475480[];
extern const float D_0032725C;
void func_0023E068(struct P *p);
void func_001CBAA0(void *pw, struct XP *list);
void func_0024E9E0(struct P *p)
{
    struct XP *list = 0;
    struct XP *x, **pp;
    struct BUCKET *b;
    func_0023E068(p);
    if (p->p2E8) {
        int f = p->p2E8->pvt->e210.pfn((char *)p->p2E8 + p->p2E8->pvt->e210.d);
        for (b = p->pw->pbucket; b; b = b->next) {
            for (pp = &b->head; (x = *pp) != 0;) {
                struct LO *o;
                if (x->kind != 0xB) {
                    { int i = (struct LO *)p == x->ae[0].object; o = x->ae[i].object; }
                    if (f ? o->pvt->e210.pfn((char *)o + o->pvt->e210.d) != 0 : o == p->p2E8) {
                        *pp = x->next;
                        x->next = list;
                        list = x;
                        continue;
                    }
                }
                pp = &x->next;
            }
        }
    }
    {
        struct XP *y, *best, **py;
        struct BUCKET *c;
        float g = D_0032725C;
        best = 0;
        c = p->pw->pbucket;
        for (;;) {
            for (y = c ? c->head : p->pw->head68; y; y = y->next) {
                if (y->kind == 0xE && y->distance < g) { g = y->distance; best = y; }
            }
            if (!c) break;
            c = c->next;
        }
        p->pxp218 = best;
        if (best) {
            p->f21C = g_clock.t;
            p->q240 = best->ae[1].pos;
        }
        c = p->pw->pbucket;
        for (;;) {
            py = c ? &c->head : &p->pw->head68;
            while ((y = *py) != 0) {
                int i = (struct LO *)p != y->ae[0].object;
                if (y->ae[i].lo == p && y->kind == 0xE && y != best) {
                    *py = y->next;
                    y->next = list;
                    list = y;
                } else py = &y->next;
            }
            if (!c) break;
            *c->ptail = c->head;
            c = c->next;
        }
    }
    func_001CBAA0(D_00475480, list);
}
