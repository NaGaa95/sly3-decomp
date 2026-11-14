// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00147FD0: Sly 3 rework of Sly 2 func_00137A30 (merge of element ENT lists into pxNew). One register pin (mF31 in s6).
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c) { cb = c; cbAlign = 0x10; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct OBJ;
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; signed f31 : 1; OBJ *pobj; };
struct X;
struct OBJ { int x0; X *px; void *ae3; OBJ **apobj; qword q10; };
struct X {
    int x0; char pad4[0x10 - 0x4]; void *x10; char pad14[0x4C - 0x14]; int c; ENT *aent; char pad54[0x5C - 0x54]; int x5C;
    char pad60[0x68 - 0x60]; float g68; char pad6C[0x88 - 0x6C]; int x88, x8C, x90; void *x94; int x98, x9C;
    char padA0[0xA8 - 0xA0]; int xA8; char padAC[0xB0 - 0xAC]; int cb; int cElem; struct ELEM *aelem; char padBC[0xC0 - 0xBC];
    void *xC0; int xC4; X *pxC8;
};
struct ELEM { float g; X *px; };
extern "C" {
void *func_00117BF0(void *pa, int cb, void *pv, int n);
void *func_00117B40(void *pa, int cb, int n);
void *func_001D2670(const AREQ &req);
void *func_00149028(int cb, void *pa);
OBJ *func_002BC378(void *pv);
OBJ *func_0012EF30(int n, void *pa);
void func_00136E28(X *px, void *p, ENT *pent, int *pa, void **ppb);
qword func_0028B388(void *pa, void *pb);
void func_002BAA50(X *px, int n);
void func_00148938(X *px);
}
#define PELEM(i) ((ELEM *)((char *)pxNew->aelem + (i) * pxNew->cb))
extern "C" void func_00147FD0(X *pxNew, void *pa)
{
    X *pxCopy = 0;
    X *pxFirst, *pxName;
    ELEM *pe;
    int i, j;
    pxNew->xA8 = 1;
    pxName = 0;
    pxFirst = 0;
    for (i = 0; i < pxNew->cElem; i++) {
        pe = PELEM(i);
        if (pe->px) {
            if (!pxFirst) pxFirst = pe->px;
            if (!pxCopy && (pe->px->x88 || pe->px->x98 || pe->px->x90)) pxCopy = pe->px;
            if (!pxName) pxName = pe->px->x0 ? pe->px : 0;
        }
    }
    if (pxCopy) {
        pxNew->pxC8 = pxCopy;
        pxNew->x88 = pxCopy->x88;
        pxNew->x8C = pxCopy->x8C;
        pxNew->x90 = pxCopy->x90;
        pxNew->x94 = func_00117BF0(pa, pxCopy->x90 * 20, pxCopy->x94, 10);
        pxNew->x98 = pxCopy->x98;
        pxNew->x9C = pxCopy->x9C;
    }
    FRAME frame;
    {
        int cTotal = 0;
        for (i = 0; i < pxNew->cElem; i++) {
            pe = PELEM(i);
            if (pe->px) cTotal += pe->px->c;
        }
        pxNew->aent = (ENT *)func_001D2670(AREQ(cTotal * 8));
        pxNew->c = 0;
    }
    for (i = 0; i < pxNew->cElem; i++) {
        pe = PELEM(i);
        if (!pe->px) continue;
        for (j = 0; j < pe->px->c; j++) {
            ENT *pent = &pe->px->aent[j];
            ENT *pentNew;
            OBJ *pobj;
            int k;
            if (pent->f30) continue;
            for (k = 0; k < pxNew->c; k++) {
                pentNew = &pxNew->aent[k];
                if ((*(unsigned *)pent & 0x3FFFFFFF) == (*(unsigned *)pentNew & 0x3FFFFFFF))
                    goto found;
            }
            pentNew = &pxNew->aent[pxNew->c++];
            pentNew->n = (*(unsigned *)pent << 12) >> 12;
            pentNew->k = pent->k;
        found:
            register unsigned mF31 asm("$22") = 0x80000000;  /* register pin: mF31 in s6 like the target */
            if (pent->f31 >= 0) {
                if (!pentNew->pobj) {
                    int a; void *pv;
                    pobj = func_002BC378(func_00149028(0x20, pa));
                    func_00136E28(pxNew, pxNew->x10, pentNew, &a, &pv);
                    if (!pv) {
                        float *pf = (float *)&pobj->q10;
                        pf[2] = 0.0f;
                        pf[1] = 0.0f;
                        pf[0] = 0.0f;
                    } else {
                        pobj->q10 = func_0028B388(pv, pv);
                    }
                    pobj->px = pxNew;
                    pobj->ae3 = pxNew->xC0;
                    pobj->apobj = (OBJ **)func_00117B40(pa, pxNew->cElem * 4, 0x12);
                    pentNew->pobj = pobj;
                } else pobj = pentNew->pobj;
            } else {
                if (!pentNew->pobj) {
                    pobj = func_0012EF30(2, pa);
                    pobj->px = pxNew;
                    pobj->ae3 = pxNew->xC0;
                    pobj->apobj = (OBJ **)func_00117B40(pa, pxNew->cElem * 4, 0x15);
                    pentNew->pobj = pobj;
                    *(unsigned *)pentNew |= mF31;
                } else pobj = pentNew->pobj;
            }
            pobj->apobj[i] = pent->pobj;
        }
    }
    pxNew->aent = (ENT *)func_00117BF0(pa, pxNew->c * 8, pxNew->aent, 8);
    pxNew->x5C = pxFirst->x5C;
    pxNew->g68 = pxFirst->g68;
    pxNew->xC4 = -1;
    if (pxName) func_002BAA50(pxNew, pxName->x0);
    for (i = 0; i < pxNew->cElem; i++) {
        pe = PELEM(i);
        pe->g = (pe->px == pxFirst) ? 1.0f : 0.0f;
    }
    func_00148938(pxNew);
}
