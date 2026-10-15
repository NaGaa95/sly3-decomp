// Sly 2 reference: src/hand/func_001ECC28.c.
// Original Sly 3 call/data operands establish the relocated symbol addresses.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct BS { int n0; int n4; int n8; };
struct X { char pad[0xC]; int c; };
struct T1 { char pad[0x18]; long l18; };
struct T2 { char pad[0x20]; long l20; };
struct E1 { int n0; unsigned char b4; char pad5[5]; unsigned short hA; int nC; int n10; char pad14[4]; long l18; };
struct E2 { int n0; unsigned char b4; char pad5[7]; unsigned char bC; char padD; unsigned short hE; char pad10[4]; int n14; int n18; char pad1C[4]; long l20; };
extern int D_00474FA0;
extern struct E1 *D_00474FA4;
extern int D_00474F98;
extern struct E2 *D_00474F9C;
struct T1 *func_00236CF0(int);
struct T2 *func_00236C18(int);
int func_00196C18(struct BS *, int);
void func_00236068(struct E1 *, int);
void func_00236150(struct E1 *, int, struct X *);
void func_002361C0(struct E2 *, int);
void func_00236298(struct E2 *, int, struct X *);
void func_00174708(struct X *, int, int);
void func_00236C80(struct E1 *);
void func_00236BA8(struct E2 *);
int func_002362D0(int k, struct BS *pbs, struct X *px)
{
    int c0 = 0;
    int i, j;
    if (px)
        c0 = px->c;
    for (i = 0; i < D_00474FA0; i++) {
        struct E1 *pe = &D_00474FA4[i];
        struct T1 *pt;
        int v;
        if (k != pe->b4)
            continue;
        pt = func_00236CF0(pe->n0);
        if (pt) {
            pe->l18 = pt->l18;
            continue;
        }
        v = func_00196C18(pbs, pe->hA);
        func_00236068(pe, v);
        if (px && pbs->n4 <= pbs->n8) {
            func_00236150(pe, v, px);
            func_00174708(px, pe->n10, pe->nC);
        }
        func_00236C80(pe);
    }
    for (j = 0; j < D_00474F98; j++) {
        struct E2 *pe = &D_00474F9C[j];
        struct T2 *pt;
        int v;
        if (k != pe->b4)
            continue;
        pt = func_00236C18(pe->n0);
        if (pt) {
            pe->l20 = pt->l20;
            continue;
        }
        if (!pe->bC) {
            int r = pbs->n4 & 0x1F;
            if (r)
                func_00196C18(pbs, 32 - r);
        }
        v = func_00196C18(pbs, pe->hE);
        func_002361C0(pe, v);
        if (px && pbs->n4 <= pbs->n8) {
            func_00236298(pe, v, px);
            func_00174708(px, pe->n18, pe->n14);
        }
        func_00236BA8(pe);
    }
    if (!px)
        return 0;
    return px->c != c0;
}
