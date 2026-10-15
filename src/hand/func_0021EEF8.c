// Process actual event buttons, record restrictions and actor assignment toggles.
// Query explicitly supplies inputA0,unsignedmaskA1 and thresholdF12=0; physical ABI view keeps this source argument order.
// SLY3_CFLAGS: -Os -G0
struct R {
    char opaque0[0x1C];
    int flags;
};
struct OBJ {
    char opaque0[0x1C];
    void *input;
    char opaque20[0x34-0x20];
    void *data;
    char opaque38[0x40-0x38];
    int cancel;
    char opaque44[0x50-0x44];
    int selected;
    char opaque54[4];
    int record;
};
typedef char EventReceiverPrefix[(sizeof(struct OBJ) == 0x5C) ? 1 : -1];

extern char D_00475480[];
extern unsigned int D_00349040[];
void func_0021EBE0(struct OBJ *);
#include "input_query_api.h"
int func_001A7AE0(void *,unsigned int,unsigned int);
void *func_001F4AD0(void *,int);
int func_0021EE68(struct OBJ *,void *);
void func_0021FAE0(struct OBJ *,int);
void func_0021EC30(struct OBJ *);
struct R *func_0021F310(struct OBJ *,int);
void func_0021ED28(struct OBJ *,int,int);
void *func_002459F8(int);
void func_00244F08(void *,int);
unsigned int func_00154798(void *,int);
void func_001548E8(void *,int,int);
void func_0021EEF8(struct OBJ *p) {
    void *actor;
    struct R *r;
    int i;
    func_0021EBE0(p);
    if(!p->data) return;
    if(p->selected == -1) return;
    if(!p->input) return;
    if(p->cancel && (func_001A7A80(p->input,0x10,0.0f) || func_001A7AE0(p->input,0x100,8))) {
        func_0021FAE0(p,-1);
        return;
    }
    actor=func_001F4AD0(D_00475480,0);
    if(!func_0021EE68(p,actor)) {
        func_0021FAE0(p,-1);
        return;
    }
    func_0021EC30(p);
    if(func_001A7A80(p->input,0x7E8,0.0f)) {
        r=func_0021F310(p,p->record);
        if(!r || !(r->flags&1)) func_0021ED28(p,1,0x137);
        else func_0021ED28(p,1,0x40);
    }
    for(i=0;i<3;++i) {
        unsigned int key=D_00349040[i];
        if(!func_001A7A80(p->input,key,0.0f)) continue;
        r=func_0021F310(p,p->record);
        if(!r || !(r->flags&4)) func_0021ED28(p,1,0x41);
        else if(!(r->flags&1)) func_0021ED28(p,1,0x42);
        else {
            func_00244F08(func_002459F8(0x34),0);
            if(func_00154798(actor,p->record)==key) func_001548E8(actor,i,-1);
            else func_001548E8(actor,i,p->record);
        }
    }
}
