// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short pad; void (*pfn)(void *); };
struct VTE2 { short d; short pad; void (*pfn)(void *, int); };
struct VT { char pad[8]; struct VTE e8; char pad10[0xB8 - 0x10]; struct VTE2 eB8; };
struct LO { char pad[0xC]; struct VT *pvt; char pad10[0x18 - 0x10]; struct LO *p18; char pad1C[0x24 - 0x1C]; struct LO *next24;
    char pad28[0x3C - 0x28]; unsigned int grf3C; char pad40[0x54 - 0x40]; struct LO *child54; char pad58[0x60 - 0x58]; struct LO *end60;
    int pad64; float f68; char pad6C[0xD8 - 0x6C]; int nD8; };
struct NODE { int kind; struct LO *plo; float g; };
struct LIST { int n0; char x4[1]; };
void func_002BBEC8(void *, int);
extern char D_0047A458[];
extern struct LO *D_00479994;
struct NODE *func_0011E118(void *pool);
void func_0011AD80(void *list, void *node);
void func_00138B68(void *p, float g);
int func_0013B500(void *object, int kind);
struct LO *func_001FE9B8(struct LO *plo);
void func_00242048(struct LO *p, struct LIST *pl);
struct TOKEN { int n; };
static inline struct NODE *NewNode() { return func_0011E118(D_0047A458); }
static inline unsigned int Grf(struct LO *plo)
{
    unsigned int grf = plo->grf3C;
    if ((grf ^ 1) & 1) grf = *(unsigned int *)grf;
    return grf;
}
void func_00242048(struct LO *p, struct LIST *pl)
{
    struct TOKEN token;
    struct LO *q, *c;
    struct NODE *n;
    if (Grf(p) & 8) {
        n = NewNode();
        n->kind = 0x2F;
        n->plo = p;
        func_0011AD80(pl->x4, n);
        p->pvt->eB8.pfn((char *)p + p->pvt->eB8.d, 0);
    }
    for (q = D_00479994; q; q = q->next24) {
        if (q->p18 != p) continue;
        n = NewNode();
        n->kind = 0xAB;
        n->plo = q;
        func_0011AD80(pl->x4, n);
        q->pvt->e8.pfn((char *)q + q->pvt->e8.d);
        func_00138B68(q, 0.0f);
    }
    for (c = p->child54; c != p->end60; c = c->next24) {
        if (func_0013B500(c, 0x2F)) {
            func_00242048(c, pl);
        } else if (func_0013B500(c, 0x2D) && c->nD8 < 4 && c->nD8 > 0) {
            struct LO *o = func_001FE9B8(c);
            if (o) {
                n = NewNode();
                n->kind = 0xC3;
                n->plo = o;
                n->g = o->f68;
                func_0011AD80(pl->x4, n);
                o->pvt->e8.pfn((char *)o + o->pvt->e8.d);
                o->f68 = 0.0f;
            }
        }
    }
    func_002BBEC8(&token, 2);
}
