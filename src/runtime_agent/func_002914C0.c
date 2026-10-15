// SLY3_CFLAGS: -Os -G0
typedef int CallbackArgument __attribute__((mode(DI)));
typedef void (*Callback)(int,CallbackArgument);
typedef struct CallbackRecord { Callback call; CallbackArgument argument; } CallbackRecord;
extern int *D_0034A260,*D_0034A280[2];
extern int D_0034A288[2],D_0034A2A0,D_0034A2A4,D_0034A2D8;
extern CallbackRecord *D_0034A290[2];
extern unsigned char D_004C4180[],D_0032A1B8[],D_0032A5D8[],D_0032A600[],D_0032A660[];
extern int D_004C41C0[3];
extern int func_00271388(const void *format,...);
extern void func_00290C00(int *buffer,int count);
extern int func_00296108(void *rpc);
extern int func_002908F0(void);
extern void func_00293920(int mode);
extern int func_00295F08(void *rpc,int command,int mode,void *send,int send_size,void *receive,int receive_size,void *callback,void *callback_argument);
extern void *func_00291E8C(void *dest,const void *src,unsigned int count);
extern void func_00291838(void);
typedef struct SpecialCommand { int opaque[2]; unsigned int count; const void *data; } SpecialCommand;

void func_002914C0(int command,int size,const unsigned char *source,Callback callback,CallbackArgument argument) {
    int packet_size;
    int tries;
    int restore_pause=0;
    unsigned char *out;
    int i;
    if(!D_0034A2A4 && !D_0034A260 && !size && !callback) {
        func_00290C00(D_004C41C0,1);
        while(func_00296108(D_004C4180)) {
            if(!D_0034A2D8) func_00271388(D_0032A1B8);
            func_002908F0();
            func_00293920(0);
        }
        func_00295F08(D_004C4180,command,1,0,0,D_004C41C0,12,0,0);
        return;
    }
    tries=0;
    packet_size=size+4;
    if(packet_size &3) packet_size+=4-packet_size%4;
    if(packet_size>512) {
        func_00271388(D_0032A5D8);
        for(;;) {}
    }
    while(*D_0034A280[D_0034A2A0]==256 || D_0034A288[D_0034A2A0]<packet_size) {
        if(D_0034A2A4) {D_0034A2A4=0;restore_pause=1;}
        func_002908F0();
        if(tries==1 && !D_0034A2D8) func_00271388(D_0032A600,D_0034A2A0,*D_0034A280[D_0034A2A0]);
        // The initial branch targets the capacity check after this increment.
        ++tries;
    }
    if(tries && !D_0034A2D8) func_00271388(D_0032A660,tries);
    if(restore_pause) D_0034A2A4=1;
    out=(unsigned char *)D_0034A280[D_0034A2A0]-(D_0034A288[D_0034A2A0]-4096);
    *(unsigned short *)out=command;out+=2;
    *(unsigned short *)out=size;out+=2;
    if(command!=104) {
        for(i=0;i<size;++i) out[i]=source[i];
    } else {
        const SpecialCommand *special=(const SpecialCommand *)source;
        for(i=0;i<12;++i) out[i]=source[i];
        func_00291E8C(out+12,special->data,special->count);
    }
    D_0034A288[D_0034A2A0]-=packet_size;
    D_0034A290[D_0034A2A0][*D_0034A280[D_0034A2A0]].call=callback;
    D_0034A290[D_0034A2A0][*D_0034A280[D_0034A2A0]].argument=argument;
    func_00291838();
}
