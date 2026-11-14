// Sly 2 counterpart: sceSifInitRpc (decomp src/lib/sceSifInitRpc.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* func_002956E0 (libkernel sifrpc). func_002980D0 (func_002980D0) must return int
   (its unused $v0 result keeps hi(pkt table) out of $v0), and the RPC data fields are set in struct order
   with pid last, as in ps2sdk's SifInitRpc. */
typedef struct {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    void *rdata_table;
    int rdata_table_len;
    void *client_table;
    int client_table_len;
    int client_table_idx;
} RpcData;
typedef struct { int x0, x4, x8, xc; } Cmd;
#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))
extern int _rpc_inited;
extern unsigned char D_004C9780[];
extern unsigned char D_004C9F80[];
extern unsigned char D_004CA780[];
extern RpcData D_004CAF80;
int func_002980D0(void);
void func_00298120(void);
void func_00299770(void);
void func_00299A28(unsigned int cid, void (*h)(void *, void *), void *data);
int sceSifGetReg(unsigned int reg);
void func_00293AA0(unsigned int reg, int val);
unsigned int func_00299C28(unsigned int cid, void *pkt, int size, void *src, void *dst, int n);
int func_00299748(int);
void func_002959E0(void *, void *);
void func_00295C58(void *, void *);
void func_00295E78(void *, void *);
void func_00295AF0(void *, void *);
void func_002956E0(unsigned int mode)
{
    Cmd *cmd;
    func_002980D0();
    if (_rpc_inited) {
        func_00298120();
        return;
    }
    _rpc_inited = 1;
    func_00298120();
    func_00299770();
    func_002980D0();
    D_004CAF80.pkt_table = UNCACHED(D_004C9780);
    D_004CAF80.pkt_table_len = 32;
    D_004CAF80.unused1 = 0;
    D_004CAF80.unused2 = 0;
    D_004CAF80.rdata_table = UNCACHED(D_004C9F80);
    D_004CAF80.rdata_table_len = 32;
    D_004CAF80.client_table = UNCACHED(D_004CA780);
    D_004CAF80.client_table_len = 32;
    D_004CAF80.client_table_idx = 0;
    D_004CAF80.pid = 1;
    func_00299A28(0x80000008, func_002959E0, &D_004CAF80);
    func_00299A28(0x80000009, func_00295C58, &D_004CAF80);
    func_00299A28(0x8000000A, func_00295E78, &D_004CAF80);
    func_00299A28(0x8000000C, func_00295AF0, &D_004CAF80);
    func_00298120();
    if (sceSifGetReg(0x80000002) != 0)
        return;
    cmd = (Cmd *)(D_004C9780 + 0x40);
    cmd->xc = 1;
    func_00299C28(0x80000002, cmd, 16, 0, 0, 0);
    while (func_00299748(0) == 0)
        ;
    func_00293AA0(0x80000002, 1);
}
