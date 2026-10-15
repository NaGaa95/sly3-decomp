#include "heap_frame_api.h"
// Complete original function, inputs and emitted data independently reviewed.
// GS allocator outputs remain integer block addresses; DMA data/output buffers are CPU pointers.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
typedef int qword __attribute__((mode(TI)));
struct BS {
    int n0;
    int n4;
    int n8;
};
struct DMAS {
    int pad[3];
    qword *pqw;
    int pad2[8];
};
struct X {
    int pad[8];
};
struct M {
    int pad[4];
};
struct E1 {
    int n0;
    unsigned char b4;
    char pad5[5];
    unsigned short hA;
    const void *dataC;
    int n10;
    char pad14[0xC];
};
struct E2 {
    int n0;
    unsigned char b4;
    char pad5[9];
    unsigned short hE;
    char pad10[4];
    const void *data14;
    int n18;
    char pad1C[0xC];
};
extern int D_00474F48;
extern int D_00474F4C;
extern int D_00474FA0;
extern struct E1 *D_00474FA4;
extern int D_00474F98;
extern struct E2 *D_00474F9C;
void func_0018C750(struct DMAS *);
void func_0027E190(struct X *);
void func_001744E8(struct X *, int);
void func_001746C0(struct X *);
void func_0027E290(struct X *);
void func_001744D8(struct DMAS *);
void func_00174538(struct DMAS *, int, void *);
int func_00196C18(struct BS *, int);
void func_00236068(struct E1 *, int);
void func_00236150(struct E1 *, int, struct DMAS *);
void func_002361C0(struct E2 *, int);
void func_00236298(struct E2 *, int, struct DMAS *);
void func_00174550(struct DMAS *, int *, void **);
void func_0027E660(struct X *, int, const void *, int);
void func_0027E6E0(struct X *, int, const void *, int);
void func_0018CA08(struct DMAS *, int, int, int);
void func_0018CCC0(struct DMAS *, int, int);
void func_0018C798(struct DMAS *);
void func_001748F8(struct X *);
void func_00174828(struct X *);
void func_001745C8(struct X *, int, int, void **);
void *func_002364F0(struct BS *pbs, int k) {
    struct DMAS dmas;
    struct X x;
    struct M m;
    char ab[0xA0];
    int cb;
    void *pv;
    void *result;
    int n4;
    int i, j;
    func_0018C750(&dmas);
    result = 0;
    func_0027E190(&x);
    n4 = pbs->n4;
    func_001D2770(&m);
    func_001744E8(&x, (D_00474F4C * 3 + D_00474F48) * 10 + 4);
    func_001746C0(&x);
    func_0027E290(&x);
    for (i = 0; i < D_00474FA0; i++) {
        struct E1 *pe = &D_00474FA4[i];
        int v;
        if (pe->b4 != k) continue;
        func_001744D8(&dmas);
        func_00174538(&dmas, 10, ab);
        v = func_00196C18(pbs, pe->hA);
        func_00236068(pe, v);
        func_00236150(pe, v, &dmas);
        *(ulong *)(dmas.pqw - 1) |= 0x8000;
        func_00174550(&dmas, &cb, &pv);
        func_0027E660(&x, cb, pv, 0);
        func_0027E6E0(&x, pe->n10, pe->dataC, 0);
    }
    for (j = 0; j < D_00474F98; j++) {
        struct E2 *pe = &D_00474F9C[j];
        int v;
        if (k != pe->b4) continue;
        func_001744D8(&dmas);
        func_00174538(&dmas, 10, ab);
        v = func_00196C18(pbs, pe->hE);
        func_002361C0(pe, v);
        func_00236298(pe, v, &dmas);
        *(ulong *)(dmas.pqw - 1) |= 0x8000;
        func_00174550(&dmas, &cb, &pv);
        func_0027E660(&x, cb, pv, 0);
        func_0027E6E0(&x, pe->n18, pe->data14, 0);
    }
    if (n4 < pbs->n4) {
        func_001744D8(&dmas);
        func_00174538(&dmas, 10, ab);
        func_0018CA08(&dmas, 0, 1, 14);
        func_0018CCC0(&dmas, 0x3F, 0);
        func_0018C798(&dmas);
        func_00174550(&dmas, &cb, &pv);
        func_0027E660(&x, cb, pv, 0);
        func_0027E290(&x);
        func_001748F8(&x);
        func_00174828(&x);
        func_001745C8(&x, 0, 0, &result);
    }
    {
        void *r = result;
        func_001D2798(&m, 2);
        return r;
    }
}
