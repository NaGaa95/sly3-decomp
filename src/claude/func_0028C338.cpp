// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_0022D7A0.cpp; target Sly 3 0x0028C338.
// Read transform records and their optional animation jobs from a binary stream.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
struct V {float f[4];} __attribute__((aligned(16)));
struct V2 {float x,y;};
struct M4 {V r[4];};
struct S;struct E;struct JOB;
struct RESOURCE {char pad[0x30];float position[3];};
struct VE {short delta,pad;RESOURCE *(*get)(void *,int);};
struct JOB {int kind;S *owner;E *entry;int order;JOB *next;int id;void *vt;};
struct J1 {JOB h;int selector;qword initial;};
struct J2 {JOB h;int pad1C;qword initial;V begin,end;V2 timingBegin,timingEnd;float g;int a,b,c;char pad70[0x10];};
struct J4 {JOB h;float lo,hi;int pad24;};
struct J9 {JOB h;int pad1C;V value;};
struct E {M4 matrix;char pad40[0x50];JOB *jobs;int kind,pad98,tag;RESOURCE *reference;int padA4;RESOURCE *origin;short lo,hi;char padB0[0x10];qword current;char padD0[0x10];qword previous;char padF0[0x10];};
struct S {char pad0[0xC];VE *vt;char pad10[0x2C];int flags;int count;E *records;RESOURCE *a,*b,*c;};
struct REQ {int size,kind;};
extern char D_003511B8[],D_00351138[],D_003510F8[],D_00350FF8[];
extern "C" {
int func_00119178(void *);
int S32Read__18CBinaryInputStream(void *);
int func_00119128(void *);
int func_00118FF8(void *);
float func_00119260(void *);
void ReadCb12(void *,V *) asm("ReadCb12__18CBinaryInputStreamPv");
void ReadCb8(void *,V2 *) asm("ReadCb8__18CBinaryInputStreamPv");
void ReadVector(void *,V *) asm("func_001192D8");
void ReadMatrix4(void *,M4 *) asm("func_00119340");
void *PvAllocSwClearImpl(REQ *) asm("func_001D2538");
void *func_0014BE38(int);
void func_002BBC38(void *);
void func_0028F068(S *,E *,int);
void *memset(void *,int,unsigned int);
qword func_0028B388(E *,E *);
void func_0028B188(S *,E *);
void func_0028ECE0(S *,E *,JOB *);
void func_0028E768(S *);
void func_001A5D10(S *,void *);
void func_00182808(S *,void *);
void func_0026EF10(S *,void *);
}
static inline J1 *CreateJ1(){J1 *j;j=(J1 *)func_0014BE38(sizeof(J1));func_002BBC38(j);j->h.vt=D_003511B8;j->h.kind=1;j->selector=2;return j;}
static inline J2 *CreateJ2(){J2 *j;j=(J2 *)func_0014BE38(sizeof(J2));func_002BBC38(j);j->h.kind=2;j->h.vt=D_00351138;return j;}
static inline J4 *CreateJ4(){J4 *j;j=(J4 *)func_0014BE38(sizeof(J4));func_002BBC38(j);j->h.kind=4;j->h.vt=D_003510F8;return j;}
static inline J9 *CreateJ9(){J9 *j;j=(J9 *)func_0014BE38(sizeof(J9));func_002BBC38(j);j->h.vt=D_00350FF8;j->h.kind=9;j->h.id=21;return j;}
static inline RESOURCE *Lookup(S *p,int id){VE *ve=&p->vt[55];return ve->get((char *)p+ve->delta,id);}
static inline int ToInt(float f){return (int)f;}
static inline void Identity(M4 *m){memset(m,0,sizeof(*m));m->r[3].f[3]=1.0f;m->r[2].f[2]=1.0f;m->r[1].f[1]=1.0f;m->r[0].f[0]=1.0f;}
static inline void ClearFlag(S *p){int f=p->flags;if((f^1)&1)*(int *)f&=~0x40;else p->flags=f&~0x40;}
extern "C" void func_0028C338(S *p,void *stream){
 int i=0;
 p->count=func_00119178(stream);
 REQ request;request.size=p->count*sizeof(E);request.kind=16;
 p->records=(E *)PvAllocSwClearImpl(&request);
 for(;i<p->count;i++){
  E *e=&p->records[i];
  e->reference=Lookup(p,func_00119178(stream));
  e->kind=func_00119178(stream);
  e->tag=S32Read__18CBinaryInputStream(stream);
  int flags=func_00118FF8(stream);
  if(flags&1){e->lo=ToInt(func_00119260(stream)*1000.0f);e->hi=1000;}
  else if(flags&2){float thousand=1000.0f;e->lo=ToInt(func_00119260(stream)*thousand);e->hi=ToInt(func_00119260(stream)*thousand);}
  else{e->lo=1000;e->hi=1000;}
  J1 *j1;J2 *j2;J4 *j4;J9 *j9;
  int has1=flags&4;
  if(has1){j1=CreateJ1();j1->h.id=func_00119128(stream);}
  int has2=flags&8;
  if(has2){j2=CreateJ2();j2->h.id=func_00119128(stream);j2->g=func_00119260(stream);ReadCb12(stream,&j2->begin);ReadCb8(stream,&j2->timingBegin);ReadCb12(stream,&j2->end);ReadCb8(stream,&j2->timingEnd);j2->a=func_00119128(stream);j2->b=func_00119128(stream);j2->c=S32Read__18CBinaryInputStream(stream);}
  int has4=flags&16;
  if(has4){j4=CreateJ4();j4->h.id=func_00119128(stream);j4->lo=func_00119260(stream);j4->hi=func_00119260(stream);}
  int has9=flags&32;
  if(has9){j9=CreateJ9();ReadVector(stream,&j9->value);}
  switch(e->kind){
  case 0:case 13:case 15:ReadMatrix4(stream,&e->matrix);break;
  case 8:case 14:{Identity(&e->matrix);e->origin=Lookup(p,func_00119178(stream));e->matrix.r[3].f[0]=-e->origin->position[0];e->matrix.r[3].f[1]=-e->origin->position[1];e->matrix.r[3].f[2]=-e->origin->position[2];break;}
  case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 9:case 10:case 11:case 12:default:
   ReadMatrix4(stream,&e->matrix);e->current=e->previous=func_0028B388(e,e);break;
  }
  func_0028B188(p,e);
  if(has1){j1->h.owner=p;j1->h.entry=e;j1->h.order=-1;j1->initial=func_0028B388(e,e);func_0028ECE0(p,e,&j1->h);}
  if(has2){j2->h.owner=p;j2->h.entry=e;j2->h.order=j2->b;j2->initial=func_0028B388(e,e);func_0028ECE0(p,e,&j2->h);}
  if(has4){j4->h.owner=p;j4->h.entry=e;j4->h.order=-1;func_0028ECE0(p,e,&j4->h);}
  if(has9){j9->h.owner=p;j9->h.entry=e;j9->h.order=-1;func_0028ECE0(p,e,&j9->h);}
  if(flags&0x40)func_0028F068(p,e,6);
 }
 func_0028E768(p);
 func_001A5D10(p,stream);
 func_00182808(p,stream);
 func_0026EF10(p,stream);
 p->a=Lookup(p,func_00119178(stream));p->b=Lookup(p,func_00119178(stream));p->c=Lookup(p,func_00119178(stream));
 if(p->count>0)ClearFlag(p);
}
