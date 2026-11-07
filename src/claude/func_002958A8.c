// Sly 2 counterpart: func_00236C28 (decomp src/lib/func_00236C28.c)
/* _rpc_get_packet (Sony libkernel sifrpc). */
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    int pad[4];
    unsigned int rec_id;  /* 0x10 */
    void *pkt_addr;       /* 0x14 */
    int pid;              /* 0x18 */
    int pad2[9];
} Pkt;
typedef struct {
    int pid;      /* 0x0 */
    Pkt *table;   /* 0x4 */
    int len;      /* 0x8 */
} RpcData;
void func_002980D0(void);
int func_00298120(void);
void *func_002958A8(RpcData *rd)
{
    Pkt *p;
    int i, len;
    func_002980D0();
    len = rd->len;
    p = rd->table;
    for (i = 0; i < len; i++, p++) {
        if (!(p->rec_id & 1)) {
            int pid;
            p->rec_id = (i << 16) | 5;
            if (++rd->pid == 1) {
                rd->pid++;
                pid = 1;
            } else {
                pid = rd->pid;
            }
            p->pkt_addr = p;
            p->pid = pid;
            func_00298120();
            return p;
        }
    }
    func_00298120();
    return 0;
}
