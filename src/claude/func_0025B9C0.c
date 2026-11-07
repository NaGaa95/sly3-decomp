// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// (Claude agent A86) search uses (pmgr->a13C + j)->n: with pmgr->a13C[j].n cse keeps &a13C[0] in a register before the
// peeled compare, the giv init reuses it and reorg fills the beq slot with it (target: beql stealing the c138 reload).
struct VTE { short d; short pad; void (*pfn)(void *); };
struct VT { char pad[0x40]; struct VTE e40; struct VTE e48; };
struct LO { char pad[0xC]; struct VT *pvt; char pad10[0x18 - 0x10]; int n18; char pad1C[0x130 - 0x1C]; int n130; };
struct ENT { int n; int pad; };
struct MGR { char pad[0x138]; int c138; struct ENT a13C[1]; };
struct SW { char pad[0x438C]; int n438C; char pad4390[0x4428 - 0x4390]; int n4428; };
extern char D_0036C700[];
extern struct LO **D_00344050[];
extern int D_00344068;
struct MGR *func_0027F8D8(struct SW *p, int n);
void *func_00292034(void *pv, int n, int cb);
int func_00185700(void *table, int i);
struct LO *func_0017E1B8(void *game, int flags, int key, void *context);
void func_001F4B00(struct SW *p, int i, struct LO *plo);
void func_001C8FB0(struct LO *plo, struct MGR *pmgr);
void func_00280010(struct MGR *pmgr);
void func_0025B9C0(struct SW *p)
{
    struct MGR *pmgr;
    struct LO *aplo[2];
    struct LO *plo;
    int i, k;
    pmgr = func_0027F8D8(p, p->n438C);
    func_00292034(aplo, 0, 8);
    for (i = 0; i < 2; i++) {
        plo = func_0017E1B8(p, 5, func_00185700(D_0036C700, i), 0);
        if (i == 0) {
            int j;
            for (j = 0; j < D_00344068 && !plo; j++)
                plo = *D_00344050[j];
        }
        if (!plo) continue;
        aplo[i] = plo;
        plo->pvt->e40.pfn((char *)plo + plo->pvt->e40.d);
        func_001F4B00(p, i, plo);
        if (pmgr) {
            int j;
            for (j = 0; j < pmgr->c138; j++)
                if ((pmgr->a13C + j)->n == plo->n18) break;
            if (j >= pmgr->c138) func_001C8FB0(plo, pmgr);
        }
    }
    for (k = 0; k < D_00344068; k++) {
        struct LO *o = *D_00344050[k];
        if (o && o != aplo[0] && o != aplo[1] && o->n130 == -1)
            o->pvt->e48.pfn((char *)o + o->pvt->e48.d);
    }
    if (pmgr) {
        func_00280010(pmgr);
        p->n4428 = p->n438C;
    }
}
