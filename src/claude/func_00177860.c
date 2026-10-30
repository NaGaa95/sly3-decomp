// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// PostEmitterLoad. Sly 2 reference: /home/claude/decomp src/hand/PostEmitterLoad__FP7EMITTER.c.
struct K { short a; short b; void (*pfn)(void); };
struct LM { float gMin; float gMax; };
struct BOX { float xMin, yMin, zMin, pad; float xMax, yMax, zMax; };
struct EMITO { void *palo; };
struct EMITB { int n0; int pad4; struct EMITO *pemito; int padC; int kind; char pad14[0x20 - 0x14]; int n20; char pad24[0x30 - 0x24]; struct BOX *pbox; };
struct VTE { short delta; short pad; void *(*pfn)(void *, void *); };
struct EMITTER {
    char pad0[0xC]; struct VTE *pvt; char pad10[0x3C - 0x10]; int grf3C; char pad40[0xD0 - 0x40];
    int nD0; struct EMITB *pemitb; char padD8[0xE0 - 0xD8];
    int kind; int nE4; struct LM lmE8; struct LM lmF0; int oidF8; char padFC[0x110 - 0xFC];
    float g110; float g114; float g118; float g11C;
};
struct ALLOCREQ { int cb; int kind; };
extern char D_00475480[];
void func_00177B38(void);
static const struct K D_003212D0 = { 0, -1, func_00177B38 };
void func_002BCB58(struct EMITTER *p);
void func_0015DC68(void *pg, struct EMITTER *p, struct K k, int n);
float func_0011E940(float gMin, float gMax);
void func_00178138(struct EMITTER *p, float g);
struct EMITTER *func_0017E1B8(void *pg, int kind, int oid, int n);
struct EMITTER *func_00150690(int cid, void *p, int oid, int n);
void *func_001D24D0(struct ALLOCREQ *preq, void *pv);
void func_001C9118(struct EMITTER *p, int n);
void func_0011AF60(void *pv, struct EMITTER *p);

static __inline__ void *PvAllocCopy(int cb, void *pv)
{
    struct ALLOCREQ req;
    req.cb = cb;
    req.kind = 0x10;
    return func_001D24D0(&req, pv);
}

static __inline__ int FPtr(int n) { return !(n & 1); }

void func_00177860(struct EMITTER *pemitter)
{
    func_002BCB58(pemitter);
    if (pemitter->pemitb->pemito->palo)
        func_0015DC68(D_00475480, pemitter, D_003212D0, 0);
    switch (pemitter->kind) {
    case 0:
        pemitter->g118 = 3.402823466e+38f;
        pemitter->g110 = func_0011E940(pemitter->lmE8.gMin, pemitter->lmE8.gMax);
        func_00178138(pemitter, func_0011E940(pemitter->lmF0.gMin, pemitter->lmF0.gMax));
        break;
    case 1:
        pemitter->g114 = pemitter->g118 = 1.0f;
        pemitter->g110 = func_0011E940(pemitter->lmE8.gMin, pemitter->lmE8.gMax);
        break;
    }
    if (pemitter->pemitb->kind == 1) {
        struct BOX *pbox = pemitter->pemitb->pbox;
        if (pemitter->pemitb->pemito->palo) {
            float dx = __builtin_fabsf(pbox->xMax - pbox->xMin);
            float dy = __builtin_fabsf(pbox->yMax - pbox->yMin);
            float dz = __builtin_fabsf(pbox->zMax - pbox->zMin);
            float g;
            if (dy < dx && dz < dx)
                g = dx;
            else if (dz < dy)
                g = dy;
            else
                g = dz;
            pemitter->g11C = g * 0.5f;
        }
    }
    if (pemitter->oidF8 != -1) {
        struct EMITTER *pemitterNew = func_0017E1B8(D_00475480, 5, pemitter->oidF8, 0);
        if (!pemitterNew) {
            struct VTE *pvte;
            void *pthis;
            pemitterNew = func_00150690(0x1B, 0, pemitter->oidF8, -1);
            pemitterNew->pemitb = PvAllocCopy(0x100, pemitter->pemitb);
            pemitterNew->pemitb->n0 = 1;
            if (pemitter->pemitb->pemito->palo) {
                pemitterNew->pemitb->pemito = PvAllocCopy(0x10, pemitter->pemitb->pemito);
                pemitterNew->pemitb->n20 = -1;
                pemitterNew->pemitb->pemito->palo = 0;
            }
            pemitterNew->kind = pemitter->kind;
            pemitterNew->nE4 = pemitter->nE4;
            pemitterNew->lmE8 = pemitter->lmE8;
            pemitterNew->lmF0 = pemitter->lmF0;
            func_001C9118(pemitterNew, 1);
            pvte = &pemitterNew->pvt[35];
            pthis = (char *)pemitterNew + pvte->delta;
            pvte->pfn(pthis, ((void *(*)(void *))pemitter->pvt[36].pfn)((char *)pemitter + pemitter->pvt[36].delta));
        }
        pemitter->nD0 = 0;
        func_0011AF60((char *)pemitterNew + 0xFC, pemitter);
        if (FPtr(pemitter->grf3C))
            *(int *)pemitter->grf3C &= ~2;
        else
            pemitter->grf3C &= ~2;
    }
}

/* Next .rodata item of the original unit (the FLT_MAX literal read by func_00178150). */
const float D_003212DC = 3.402823466e+38f;
