// Sly 2 reference: src/hand/func_00118380.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct VTE { short d; short pad; void *(*pfn)(void *, int, int); } VTE;
typedef struct ALLOC { VTE *pvt; } ALLOC;
typedef struct CBinaryInputStream CBinaryInputStream;

int func_00119048(CBinaryInputStream *pbis);
void func_00118DA0(CBinaryInputStream *pbis, int cb, void *pv);

void func_00119790(CBinaryInputStream *pbis, char **ppchz, ALLOC *palloc, int nKind)
{
    int cch = func_00119048(pbis);
    char *pchz;
    if (cch == 0) {
        *ppchz = 0;
        return;
    }
    pchz = (char *)palloc->pvt[1].pfn((char *)palloc + palloc->pvt[1].d, cch + 1, nKind);
    func_00118DA0(pbis, cch, pchz);
    pchz[cch] = 0;
    *ppchz = pchz;
}
