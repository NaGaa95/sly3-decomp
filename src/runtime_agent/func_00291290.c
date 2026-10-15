// SLY3_CFLAGS: -Os -G0
extern unsigned char D_004C4200[],D_004C4180[],D_0032A590[],D_0032A1B8[];
extern int D_004C41C0[3];
extern int *D_0034A260,*D_0034A280[2];
extern int D_0034A2A0,D_0034A2A4,D_0034A2D8;
extern void func_00271388(const void *message);
extern int func_002908F0(void);
extern void func_00293920(int mode);
extern int func_00296108(void *rpc);
extern void func_00290C00(int *buffer,int count);
extern void *func_00291E8C(void *dest,const void *src,unsigned int count);
extern int func_00295F08(void *rpc,int command,int mode,void *send,int send_size,void *receive,int receive_size,void *callback,void *callback_argument);
extern int func_00290B30(void);
extern void func_00291878(void);
typedef struct SpecialCommand { int opaque[2]; unsigned int count; const void *data; } SpecialCommand;

int func_00291290(int command,int size,const unsigned char *source) {
    int i;
    int result;
    if(command!=104) {
        for(i=0;i<size;++i) D_004C4200[i]=source[i];
    } else {
        const SpecialCommand *special=(const SpecialCommand *)source;
        if(special->count+12>512U) {
            func_00271388(D_0032A590);
            for(;;) {}
        }
        for(i=0;i<12;++i) D_004C4200[i]=source[i];
        func_00291E8C(D_004C4200+12,special->data,special->count);
    }
    while(D_0034A260) {
        func_002908F0();
        func_00293920(0);
    }
    func_00290C00(D_004C41C0,1);
    while(func_00296108(D_004C4180)) {
        if(!D_0034A2D8) func_00271388(D_0032A1B8);
        func_002908F0();
        func_00293920(0);
    }
    if(size) func_00295F08(D_004C4180,command,1,D_004C4200,size,D_004C41C0,12,0,0);
    else func_00295F08(D_004C4180,command,1,0,0,D_004C41C0,12,0,0);
    while(!func_00290B30()) {}
    result=D_004C41C0[1];
    if(*D_0034A280[D_0034A2A0] && !D_0034A2A4) func_00291878();
    return result;
}
