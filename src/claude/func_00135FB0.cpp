// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Load a state-machine description from a binary stream (Sly 2 func_0012F2A8 evolved); owns jtbl 0x31F880. */
struct CBinaryInputStream {
    int U16Read();
    int S32Read();
    int S16Read() __asm__("func_00119178");
    int S8Read() __asm__("func_00119128");
    int U32Read() __asm__("func_001190A8");
    int U8Read() __asm__("func_00118FF8");
};
typedef CBinaryInputStream BIS;
struct HEAP;
struct OBJ { virtual void Load(BIS *pbis, HEAP *pheap); };
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; unsigned f31 : 1; void *pobj; };
struct ENT2 { int a; int b; OBJ *pobj; };
struct X { char pad[0x4C]; int c; ENT *aent; int c2; ENT2 *aent2; char pad5C[0x64 - 0x5C]; float g64;
    char pad68[0x88 - 0x68]; int x88, x8C, x90, x94, x98, x9C; };
struct ALLOCREQ { int cb; int cbAlign; };
void *PvAllocSlot(ALLOCREQ *);
struct CTX { int a[4]; CTX(); ~CTX(); };
extern "C" {
extern char **D_0036B160;
extern char D_004799E8[], D_004799F8[];
char *func_00117B98(HEAP *, int, int, int);
void *func_00117B40(HEAP *, int, int);
void func_0012D078(char *, BIS *);
void *func_0012D300(int, HEAP *);
OBJ *func_002BBD40(void *);
void *func_0012E080(int, HEAP *);
OBJ *func_002BBD78(void *);
void *func_0012D8E0(int, HEAP *, int);
OBJ *func_002BBDB0(void *);
void *func_0012DEA8(int, HEAP *, int);
OBJ *func_002BBDE8(void *);
void *func_0012E7B8(int, HEAP *, int);
OBJ *func_002BBE20(void *);
void *func_0012EED8(int, HEAP *, int);
OBJ *func_002BBE58(void *);
OBJ *func_0012EF30(int, HEAP *);
void func_001364A0(X *, BIS *, HEAP *, int, int *, int *);
}
static inline ALLOCREQ *Req(ALLOCREQ *preq, int cb, int cbAlign)
{
    preq->cb = cb;
    preq->cbAlign = cbAlign;
    return preq;
}

extern "C" void func_00135FB0(X *px, BIS *pbis, HEAP *pheap)
{
    px->g64 = pbis->U16Read() * (1.0f / 60.0f);
    CTX ctx;
    int cstr = pbis->U16Read();
    ALLOCREQ req;
    D_0036B160 = (char **)PvAllocSlot(Req(&req, cstr * 4, 0x10));
    char *pb = func_00117B98(pheap, pbis->U16Read(), 4, 0xB);
    for (int i = 0; i < cstr; i++) {
        char *pbCur = pb;
        D_0036B160[i] = pb;
        func_0012D078(pb, pbis);
        pb += 2;
        if (!pbCur[0])
            pb += (unsigned char)pbCur[1];
        else
            pb += (unsigned char)pbCur[1] * 2;
    }
    px->c = pbis->S16Read();
    px->aent = (ENT *)func_00117B40(pheap, px->c * 8, 9);
    for (int i = 0; i < px->c; i++) {
        ENT *pe = &px->aent[i];
        pe->n = pbis->S32Read();
        pe->k = pbis->S16Read();
        int k = pbis->S8Read();
        switch (k) {
        case -1:
            pe->f31 = 1;
            break;
        case 0:
            pe->pobj = D_004799E8;
            break;
        case 1:
            pe->pobj = D_004799F8;
            break;
        case 2: {
            OBJ *po = func_002BBD40(func_0012D300(0x10, pheap));
            pe->pobj = po;
            po->Load(pbis, pheap);
            break;
        }
        case 3: {
            OBJ *po = func_002BBD78(func_0012E080(0xC, pheap));
            pe->pobj = po;
            po->Load(pbis, pheap);
            break;
        }
        case 4:
        case 5:
        case 6:
        case 7: {
            int n = pbis->U32Read();
            switch (k) {
            case 4:
                pe->pobj = func_002BBDB0(func_0012D8E0(0x10, pheap, n));
                break;
            case 5:
                pe->pobj = func_002BBDE8(func_0012DEA8(0x10, pheap, n));
                break;
            case 6:
                pe->pobj = func_002BBE20(func_0012E7B8(0xC, pheap, n));
                break;
            case 7:
                pe->pobj = func_002BBE58(func_0012EED8(0xC, pheap, n));
                break;
            }
            ((OBJ *)pe->pobj)->Load(pbis, pheap);
            break;
        }
        }
        int id = pbis->S8Read();
        if (id != -1) {
            OBJ *po = func_0012EF30(id, pheap);
            pe->pobj = po;
            po->Load(pbis, pheap);
            pe->f31 = 1;
        }
        pe->f30 = pbis->U8Read() != 0;
    }
    px->c2 = pbis->U8Read();
    px->aent2 = (ENT2 *)func_00117B40(pheap, px->c2 * 12, 9);
    for (int j = 0; j < px->c2; j++) {
        ENT2 *pe = &px->aent2[j];
        pe->a = pbis->U8Read();
        pe->b = pbis->S32Read();
        pe->pobj = func_0012EF30(pbis->S8Read(), pheap);
        pe->pobj->Load(pbis, pheap);
    }
    func_001364A0(px, pbis, pheap, 0, &px->x88, &px->x8C);
    func_001364A0(px, pbis, pheap, 1, &px->x90, &px->x94);
    func_001364A0(px, pbis, pheap, 0, &px->x98, &px->x9C);
    D_0036B160 = 0;
}
