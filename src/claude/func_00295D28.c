// Sly 2 counterpart: sceSifBindRpc (decomp src/lib/sceSifBindRpc.c)
// (Claude agent, -Os sweep) MATCH: needed -fstrict-aliasing
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY3_ASM: gnu-reorder-db
typedef struct {
    int pad[5];
    void *pkt_addr;   /* 0x14 */
    int rec_id;       /* 0x18 */
    void *cd;         /* 0x1C */
    unsigned int sid; /* 0x20 */
} BindPkt;
typedef struct {
    void *pkt;   /* 0x00 */
    int id;      /* 0x04 */
    int sema;    /* 0x08 */
    int mode;    /* 0x0C */
    void *buff;  /* 0x10 */
    int x14, x18, x1c, x20;
    void *serve; /* 0x24 */
} ClientData;
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern char D_004CAF80[];
extern char D_0032A9D8[];
void *func_002958A8(void *);
void func_00295950(void *);
int func_002936A0(struct SemaParam *);
int func_00299C28(unsigned int, void *, int, void *, void *, int);
int func_002936B0(int);
int func_002936E0(int);
int func_00295D28(ClientData *bd, unsigned int request, unsigned int mode)
{
    BindPkt *bind;
    struct SemaParam sema;

    bd->buff = 0;
    bd->serve = 0;
    bind = (BindPkt *)func_002958A8(D_004CAF80);
    if (bind == 0) return -1;
    bd->pkt = bind;
    bd->id = bind->rec_id;
    bind->sid = request;
    bind->pkt_addr = bind;
    bind->cd = bd;

    if (!(mode & 1)) {
        sema.maxCount = 1;
        sema.option = (unsigned int)D_0032A9D8;
        sema.initCount = 0;
        bd->sema = func_002936A0(&sema);
        if (bd->sema < 0) {
            func_00295950(bind);
            return -3;
        }
        if (func_00299C28(0x80000009, bind, 0x40, 0, 0, 0) == 0) {
            func_00295950(bind);
            func_002936B0(bd->sema);
            return -2;
        }
        func_002936E0(bd->sema);
        func_002936B0(bd->sema);
    } else {
        bd->sema = -1;
        if (func_00299C28(0x80000009, bind, 0x40, 0, 0, 0) == 0) {
            func_00295950(bind);
            return -2;
        }
    }
    return 0;
}
