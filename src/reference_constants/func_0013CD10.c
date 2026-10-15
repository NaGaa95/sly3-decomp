// Reference algorithm: src/hand/func_00134320.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x48]; struct O *pnext; };
struct L { char pad[0xDC]; struct O *fec; };
struct G { char pad[0x44AC]; struct O *pfirst; };
void func_0023DD40(struct L *);
void func_0013C388(struct G *, struct O *, struct O *, int);
void func_0013CD10(struct G *pg, struct L *pl) {
    struct O *po;
    if (pl->fec) {
        func_0023DD40(pl);
        for (po = pg->pfirst; po; po = po->pnext)
            if (po != pl->fec) func_0013C388(pg, pl->fec, po, 0);
    }
}
