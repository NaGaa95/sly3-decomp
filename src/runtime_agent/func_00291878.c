// SLY3_CFLAGS: -Os -G0
extern int *D_0034A280[2];
extern int D_0034A288[2];
extern int *D_0034A298[2];
extern int D_0034A2A0,D_0034A2D8;
extern unsigned char D_0032A1B8[],D_004C4180[];
extern void func_00290C00(int *buffer,int count);
extern int func_00296108(void *rpc);
extern void func_00271388(const void *message);
extern void func_00293920(int mode);
extern int func_00295F08(void *rpc,int command,int mode,void *send,int send_size,void *receive,int receive_size,void *callback,void *callback_argument);
void func_00291878(void) {
    int next;
    func_00290C00(D_0034A298[D_0034A2A0],*D_0034A280[D_0034A2A0]);
    while(func_00296108(D_004C4180)) {
        if(!D_0034A2D8) func_00271388(D_0032A1B8);
        func_00293920(0);
    }
    func_00295F08(D_004C4180,77,1,D_0034A280[D_0034A2A0],4096-D_0034A288[D_0034A2A0],D_0034A298[D_0034A2A0],*D_0034A280[D_0034A2A0]*4+8,0,0);
    next=(D_0034A2A0 != 1);
    D_0034A2A0=next;
    *D_0034A280[next]=0;
    D_0034A288[next]=4092;
}
