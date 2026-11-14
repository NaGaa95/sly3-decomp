// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00151D80: keep-alive asm on cb in the func_001FA778 path.
struct VT { short d; short pad; void *f; };
struct IF { struct VT *vt; int x4; int x8; };
struct LO { char pad[0xC]; struct VT *vt; char pad2[0x40 - 0x10]; int x40; char pad3[0x50 - 0x44]; int x50; };
struct G { char pad[0x4634]; int x4634; int x4638; };
extern struct VT D_00353C78[];
extern struct G D_00475480;
void OBJECT_COLLECTION_BASE_ctor(struct IF *p) __asm__("__22OBJECT_COLLECTION_BASE");
int func_00119178(void *pbis);
int func_00119128(void *pbis);
int func_00118FF8(void *pbis);
int func_001191E0(void *pbis);
void func_00118DA0(void *pbis, int cb, void *pv);
void func_00118DF0(void *pbis, int cb);
int func_001FA5A8(int, int);
int func_001FA640(int, int, int *);
int func_0017E1B8(struct G *, int, int, int, int);
int func_0017E1D8(struct G *, int, int, int, int);
int func_00151C98(int c, short *a);
int func_00151D10(int c, int *a);
int func_0013BEC8(int, int);
struct LO *func_00150690(int cid, void *psw, int oid, int n);
void func_001FA778(struct G *, void *psw, int cid, int oid, int n, void *pbis, struct IF *pif);

#define VCALL1(p, n, a) ((void (*)(void *, void *))(void*)(p)->vt[n].f)((char *)(p) + (p)->vt[n].d, a)
#define VCALL2(p, n, a, b) ((void (*)(void *, int, void *))(void*)(p)->vt[n].f)((char *)(p) + (p)->vt[n].d, a, b)

void func_00151D80(void *psw, void *pbis, struct IF *pifParent)
{
    struct IF obj;
    short as[0x80];
    int ai[0x80];
    int t;
    struct LO *plo1;
    struct LO *plo2;
    int cid, oid, cb, n;
    int c;
    int i;
    int c1, c2;
    OBJECT_COLLECTION_BASE_ctor(&obj);
    obj.vt = D_00353C78;
    obj.x4 = -1;
    obj.x8 = -1;
    c = func_00119178(pbis);
    for (i = 0; i < c; i++) {
        int k = func_00119128(pbis);
        struct IF *pif;
        switch (k) {
        case 0: case 2: case 3:
            c2 = 0;
            c1 = 0;
            break;
        case 1:
            c1 = func_00118FF8(pbis);
            c2 = func_00118FF8(pbis);
            func_00118DA0(pbis, c1 * 2, as);
            func_00118DA0(pbis, c2 * 4, ai);
            break;
        }
        pif = pifParent;
        cid = func_00119178(pbis);
        oid = func_001191E0(pbis);
        n = func_00119178(pbis);
        cb = func_001191E0(pbis);
        switch (k) {
        case 2: case 3: {
            struct G *pg = &D_00475480;
            int r;
            t = func_001FA5A8(pg->x4638, -1);
            r = func_001FA640(pg->x4634, 1, &t);
            if (k == 2) {
                if (func_0017E1B8(pg, 0x405, oid, 0, r))
                    goto skip;
                obj.x4 = 1;
            } else {
                if (func_0017E1D8(pg, 0x805, oid, 0, r))
                    goto skip;
                obj.x4 = 0;
            }
            obj.x8 = t;
            pif = &obj;
            break;
        }
        case 0: pif = pifParent; break;
        case 1:
            if (func_00151C98(c1, as) && func_00151D10(c2, ai))
                goto create;
            if (cid == 0xA8 || cid == 0xA9) {
                plo1 = func_00150690(cid, psw, oid, -1);
                if (cid == 0xA8)
                    plo1->x50 = 1;
                else
                    plo1->x40 = 1;
                VCALL1(plo1, 14, pbis);
                if (pifParent)
                    VCALL2(pifParent, 1, 1, &plo1);
                continue;
            }
            goto skip;
        }
    create:
        if (func_0013BEC8(cid, 8)) {
            func_001FA778(&D_00475480, psw, cid, oid, n, pbis, pif);
            __asm__("" : : "r"(cb)); /* zero-instruction keep-alive: extends cb's life so global-alloc ranks it just above psw (cb -> fp, psw spilled) */
        } else {
            plo2 = func_00150690(cid, psw, oid, n);
            VCALL1(plo2, 14, pbis);
            if (pif)
                VCALL2(pif, 1, 1, &plo2);
        }
        continue;
    skip:
        func_00118DF0(pbis, cb);
    }
}
