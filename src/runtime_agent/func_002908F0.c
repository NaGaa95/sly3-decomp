// SLY3_CFLAGS: -Os -G0
typedef int CallbackArgument __attribute__((mode(DI)));
typedef void (*Callback)(int,CallbackArgument);
typedef struct CallbackRecord { Callback call; CallbackArgument argument; } CallbackRecord;
extern int *D_0034A260,*D_0034A280[2],*D_0034A298[2];
extern CallbackRecord *D_0034A290[2],D_0034A2B0;
extern int D_0034A27C,D_0034A2A0,D_0034A2A4,D_0034A2A8,D_0034A274,D_0034A278;
extern Callback D_0034A2C4;
extern CallbackArgument D_0034A2C8;
extern void (*D_0034A270)(int);
extern volatile unsigned int D_004C8E00;
extern int D_004C41C4;
extern void func_00293CF8(void *begin,void *end);
extern int func_00290B30(void);
extern void func_00293920(int mode);
extern void func_00291878(void);
extern int func_00291A10(int mode);

int func_002908F0(void) {
    if(D_0034A260 && func_00290B30()) {
        if(D_0034A27C) {
            if(D_0034A2C4) D_0034A2C4(D_004C41C4,D_0034A2C8);
            D_0034A2C4=0;
            D_0034A27C=0;
        } else {
            int slot=(D_0034A2A0 !=1);
            int i=0;
            for(;i<*D_0034A280[slot];++i) {
                // The original callback record stride is 16 bytes (pointer, padding, 64-bit argument).
                CallbackRecord *record=(CallbackRecord *)((unsigned int)i*sizeof(CallbackRecord)+(unsigned int)D_0034A290[slot]);
                if(record->call) record->call(D_0034A298[slot][i+1],record->argument);
            }
        }
    }
    if(D_0034A2A8) {
        func_00293CF8((void *)&D_004C8E00,(char *)&D_004C8E00+4);
        if(D_004C8E00!=0xFFFFFFFFU) {
            Callback call;
            func_00293920(0);
            call=D_0034A2B0.call;
            if(call) {
                CallbackArgument argument=D_0034A2B0.argument;
                D_0034A2B0.call=0;
                D_0034A2B0.argument=0;
                call(D_004C8E00,argument);
            }
            D_004C8E00=0;
            D_0034A2A8=0;
        }
    }
    if(!D_0034A260 && *D_0034A280[D_0034A2A0] && !D_0034A2A4) func_00291878();
    if(D_0034A274) {
        func_00291A10(1);
        if(D_0034A278) {
            D_0034A274=0;
            D_0034A278=0;
            if(D_0034A270) D_0034A270(1);
        }
    }
    if(D_0034A260 || D_0034A2A8) return 1; return 0;
}
