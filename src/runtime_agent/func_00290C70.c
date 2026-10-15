// SLY3_CFLAGS: -Os -G0
extern int D_0034A268,D_0034A2A8,D_0034A2D8;
extern volatile unsigned int D_004C8E00;
extern int D_004C8E40[2];
extern unsigned char D_004C8DC0[],D_0032A240[],D_0032A270[],D_0032A290[],D_0032A1B8[];
extern void func_00271388(const void *message);
extern int func_00291A10(int mode);
extern void func_00293BC8(void *begin,void *end);
extern int func_002908F0(void);
extern void func_00293920(int mode);
extern int func_00296108(void *rpc);
extern int func_00295F08(void *rpc,int command,int mode,void *send,int send_size,void *receive,int receive_size,void *callback,void *callback_argument);

int func_00290C70(int first,int second) {
    D_0034A268=0;
    if(D_0034A2A8) {
        if(!D_0034A2D8) func_00271388(D_0032A240);
        return 0;
    }
    if(func_00291A10(1)==1) {
        if(!D_0034A2D8) func_00271388(D_0032A270);
        return 0;
    }
    D_004C8E00=0xFFFFFFFFU;
    func_00293BC8((void *)&D_004C8E00,(char *)&D_004C8E00+4);
    D_004C8E40[0]=first;
    D_004C8E40[1]=second;
    while(func_00296108(D_004C8DC0)) {
        if(!D_0034A2D8) func_00271388(D_0032A1B8);
        func_002908F0();
        func_00293920(0);
    }
    if(func_00295F08(D_004C8DC0,3,1,D_004C8E40,8,(void *)&D_004C8E00,4,0,0)<0) {
        if(!D_0034A2D8) func_00271388(D_0032A290);
        D_0034A268=262;
        return 0;
    }
    while(D_004C8E00==0xFFFFFFFFU) func_00293920(0);
    return D_004C8E00;
}
