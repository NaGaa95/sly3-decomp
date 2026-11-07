// Sly 2 counterpart: sceSifCallRpc (decomp src/lib/sceSifCallRpc.c)
// (Claude agent) MATCH. volatile reads of end_param/rec_id emulate Sony's scheduler keeping both loads ahead of the stores.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct {
    int pad[5];
    void *pkt_addr;     /* 0x14 */
    int rec_id;         /* 0x18 */
    void *client;       /* 0x1C */
    unsigned int fno;   /* 0x20 */
    int ssize;          /* 0x24 */
    void *receive;      /* 0x28 */
    int rsize;          /* 0x2C */
    int rmode;          /* 0x30 */
    void *server;       /* 0x34 */
} CallPkt;
typedef void (*EndFunc)(void *);
typedef struct {
    void *pkt;   /* 0x00 */
    int id;      /* 0x04 */
    int sema;    /* 0x08 */
    int mode;    /* 0x0C */
    void *buff;  /* 0x10 */
    void *cbuff; /* 0x14 */
    void *gp;    /* 0x18 */
    EndFunc end_function; /* 0x1C */
    void *end_param;      /* 0x20 */
    void *server; /* 0x24 */
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
extern char D_0032A9E8[];
void *func_002958A8(void *);
void func_00295950(void *);
int func_002936A0(struct SemaParam *);
int func_00299C28(unsigned int, void *, int, void *, void *, int);
int func_002936B0(int);
int func_002936E0(int);
void func_00299DF0(void *, int);
int func_00295F08(ClientData *bd, unsigned int fno, unsigned int mode, void *send, int ssize,
                  void *receive, int rsize, EndFunc end_function, void *end_param)
{
    CallPkt *call;
    void *srv;
    struct SemaParam sema;
    void *gp;

    call = (CallPkt *)func_002958A8(D_004CAF80);
    if (call == 0) return -1;
    {
        void *ep = *(void * volatile *)&end_param;
        int id = *(volatile int *)&call->rec_id;
        bd->end_param = ep;
        bd->id = id;
    }
    bd->pkt = call;
    bd->end_function = end_function;
    __asm__ __volatile__("move %0, $gp" : "=r"(gp));
    bd->gp = gp;
    call->fno = fno;
    call->ssize = ssize;
    call->receive = receive;
    call->rsize = rsize;
    call->pkt_addr = call;
    srv = bd->server;
    call->client = bd;
    call->server = srv;

    if (!(mode & 2)) {
        if (send == receive) {
            func_00299DF0(send, ssize < rsize ? rsize : ssize);
        } else {
            if (ssize > 0) func_00299DF0(send, ssize);
            if (rsize > 0) func_00299DF0(receive, rsize);
        }
    }

    if (mode & 1) {
        if (end_function == 0) call->rmode = 0;
        else call->rmode = 1;
        bd->sema = -1;
        if (func_00299C28(0x8000000A, call, 0x40, send, bd->cbuff, ssize) != 0)
            return 0;
        func_00295950(call);
        return -2;
    }
    sema.initCount = 0;
    sema.option = (unsigned int)D_0032A9E8;
    sema.maxCount = 1;
    bd->sema = func_002936A0(&sema);
    if (bd->sema < 0) {
        func_00295950(call);
        return -3;
    }
    call->rmode = 1;
    if (func_00299C28(0x8000000A, call, 0x40, send, bd->cbuff, ssize) != 0) {
        func_002936E0(bd->sema);
        func_002936B0(bd->sema);
        return 0;
    }
    func_002936B0(bd->sema);
    func_00295950(call);
    return -2;
}
