// Reference algorithm: src/hand/func_001252D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; void *pv; } u; } CRef;
typedef struct NODE { CRef ref; int unknown8; struct NODE *pnext; } NODE;
typedef struct ARR { int c; short *a; } ARR;
short *func_001D25B0(AREQ *preq);
void func_00127220(NODE *pnode, ARR *parr)
{
    NODE *p;
    int i;
    parr->c = 0;
    parr->a = 0;
    for (p = pnode; p; p = p->pnext)
        parr->c++;
    if (parr->c) {
        AREQ req;
        req.cb = parr->c * 2;
        req.cbAlign = 0x10;
        parr->a = func_001D25B0(&req);
        for (p = pnode, i = 0; p; p = p->pnext, i++) {
            if (p->ref.m_tagk == 0x13 || p->ref.m_tagk == 0x16)
                { int n = p->ref.u.n; parr->a[i] = n; }
        }
    }
}
