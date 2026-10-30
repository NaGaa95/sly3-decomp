// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00173A68).
// g_clock (g_clock) must be a struct: a scalar float global is assumed not to alias the struct-field stores, which lets gcc CSE the clock reloads.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct VT{short delta,pad;void*fn;};
struct LO{char pad[0xC];struct VT*vt;char pad10[0x10D0-0x10];void*x10D0;};
struct SELECTOR{int kind;char pad4[0x18];int used;};
struct ENTRY{struct LO*object;float time,wait;struct SELECTOR*selector;int status;char pad14[12];qword point;};
struct EVENT{float time;char pad4[8];struct LO*tag;char pad10[0x10];struct EVENT*next;char pad24[4];int kind;struct LO*previous;};
struct P{char pad[0xC];struct VT*vt;char pad10[0x48-0x10];int count,capacity;char pad50[0x10];qword last;char pad70[0x98-0x70];float delay;float next;int mode;int tagged;};
struct M3{qword r[3];};
struct LINK{struct LO**pp;};
struct CRef{int tag;void*value;};
extern char D_00475480[];
struct CLOCK{float t,dt;};extern struct CLOCK g_clock;
void func_001C8168(struct P*);
int func_0013B500(struct LO*,int);
void func_0019A030(struct P*);
void func_001995B8(struct P*,qword);
qword func_00199270(struct P*);
struct LO*func_001F4AD0(void*,int);
struct EVENT*func_00241AA0(struct LO*);
struct ENTRY*func_00199728(struct P*,struct LO*);
struct SELECTOR*func_001997D8(struct P*,qword,qword*,struct M3*,int*);
void func_00199118(struct P*,struct ENTRY*,int,int);
struct LO*func_00199D48(struct P*,struct SELECTOR*,qword*,struct M3*,int);
void func_002413E0(struct LO*,float);
void func_00241338(struct LO*,float);
void func_001703C8(void*,struct LO*,int);
static inline float DistanceXY(qword a,qword b){qword d;float f;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(d));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
void func_001992D8(struct P*p){
 U point;
 struct M3 rotation;
 int flag;
 struct LO*object;
 struct LINK link;
 qword pos;
 struct EVENT*event;
 struct ENTRY*entry;
 struct SELECTOR*selector;
 struct LO*context;
 func_001C8168(p);
 context=func_001F4AD0(D_00475480,0);
 if(context&&func_0013B500(context,0x45)){func_0019A030(p);return;}
 pos=func_00199270(p);
 func_001995B8(p,pos);
 if(g_clock.t<p->next)return;
 p->next=g_clock.t+1.0f;
 if(p->count==p->capacity&&DistanceXY(pos,p->last)<300.0f)return;
 event=0;
 {
 if(context){
  event=func_00241AA0(context);
  if(event){
   if(!event->kind)event=0;
   else switch(p->mode){
   case 0:return;
   case 1:if(g_clock.t-event->time>2.0f)return;break;
   case 2:break;
   }
  }
 }
 }
 entry=func_00199728(p,event&&event->kind==1?event->previous:0);
 if(!entry)return;
 selector=func_001997D8(p,pos,&point.q,&rotation,&flag);
 if(!selector)return;
 p->last=pos;
 if(entry->object)func_00199118(p,entry,0,1);
 object=func_00199D48(p,selector,&point.q,&rotation,flag);
 if(!object)return;
 func_002413E0(object,0.01f);
 func_00241338(object,0.5f);
 if(event&&p->tagged)func_001703C8(object->x10D0,event->tag,2);
 entry->object=object;
 entry->time=g_clock.t;
 entry->selector=selector;
 p->count++;
 selector->used=1;
 link.pp=&object;
 {float t=g_clock.t+p->delay;p->next=p->next<t?t:p->next;}
 ((void(*)(void*,int,int,int,void*const*,struct CRef*))p->vt[3].fn)((char*)p+p->vt[3].delta,0x1C,0,1,(void*const*)&link,0);
}

