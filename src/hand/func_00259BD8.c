// Test the five original transformed points through the concrete collision filter and float bounds.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Actor {
    char prefix[0x218];
    void *attached;
    char gap[0xED4];
    int state;
};
struct S {
    struct Actor *actor;
    char gap[8];
    int blocked;
};
typedef int (*Filter)(void *query,void *hit);
extern QWORD D_003274E0[5];
int func_002533C0(void *receiver,int bit);
QWORD func_001C9428(void *source,void *destination,QWORD point);
int func_00259B78(void *query,void *hit);
int func_00198D78(QWORD *position,int flags,Filter filter,float upper,float lower);
int func_00259BD8(struct S *p) {
    unsigned int index;
    if(p->blocked>0)return 0;
    if(p->actor->attached)return 0;
    if(p->actor->state!=-1)return 0;
    if(func_002533C0(p->actor,0x26))return 0;
    index=0;
    do {
        QWORD point=func_001C9428(p->actor,0,D_003274E0[index]);
        if(func_00198D78(&point,0,func_00259B78,100.0f,-600.0f))break;
        ++index;
    }
    while(index<5);
    return !(index<5);
}
