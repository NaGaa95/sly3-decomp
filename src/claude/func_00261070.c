// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VE { short d; short pad; void (*pf)(void *); };
struct S {
    char pad0[0xC]; struct VE *vt; char pad10[0x48-0x10]; int state; float time; int tick; int mode; float update;
    char pad1[4]; int id0; int id1; int id2; char pad2[0x94-0x6C]; int flag; char pad3[8]; int pauses;
};
struct G { char pad[0x4338]; int count; };
struct Clock { char pad[0x40]; float time; float dt; };
extern struct G D_00475480;
extern struct Clock g_clock;
extern int D_0036AEB4;
extern int D_0036C650;
void func_00165548(struct Clock *,int,float);
void func_00260A60(struct S *);
void func_00260CC8(struct S *);
void func_00262188(struct S *,int);
void func_00261070(struct S *p,int state) {
    if(p->state==state) return;
    if(p->flag>=32) {
        if(p->state<2 && state>=2) D_00475480.count++;
        else if(state<2 && p->state>=2) D_00475480.count--;
    }
    if(p->pauses) {
        if(p->state<2 && state>=2) {
            if(++D_0036AEB4==1) func_00165548(&g_clock,7,0.0f);
        } else if(state<2 && p->state>=2) {
            if(--D_0036AEB4==0) func_00165548(&g_clock,7,1.0f);
        }
    }
    if(p->state==0) func_00260A60(p);
    p->state=state;
    p->time=g_clock.time;
    p->tick=D_0036C650;
    switch(state) {
    case 0: func_00260CC8(p); break;
    case 1: p->vt[57].pf((char *)p + p->vt[57].d); break;
    case 2: func_00262188(p,p->id0); break;
    case 3: func_00262188(p,p->id1); break;
    case 4: func_00262188(p,p->id2); break;
    }
}
/* The rest of this unit's .rodata (used by func_00261C08); defined here so the jump table's
   16-byte-padded section matches. */
const char D_00327F28[] __attribute__((aligned(8))) = "swf";
