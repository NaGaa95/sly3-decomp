// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00182068: pick a reachable point near the actor (Sly 2 func_0017BFF8 lane H14 source adapted: actor fields at 0x34C/0x3D8,
// func_002575C0 returns the range scale, position via the vtable matrix, FLT_MAX literal = RO 0x321860).
// The first func_00120A00 argument is read from an uninitialized local, as in the original (lq a0,0x370(sp)).
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct LM{float low,high;};
struct TUNING{char pad[0x10];int override;float narrow,wide;};
struct M4{qword r[4];};struct LO;struct LOV{char pad[0x120];short d;short p;M4*(*pfnMat)(LO*);};struct LO{int a[3];LOV*pvt;};
struct SCALE{char pad[0x20];float value;};
struct ACTOR{LO lo;char pad10[0x34C-0x10];LM first,second;char pad35C[0x3D8-0x35C];TUNING*tuning;};
struct P{char pad[0x10];ACTOR*actor;};
struct FLOW{float polarAngle,polarLength,candidateAngle,candidateLength,distance;};
struct SEGMENT{qword a,b;char data[0x40];};
extern "C"{
float func_002575C0(ACTOR*);
void func_00120B00(qword,float*,float*,float*);
float func_0011E3B8(float);float func_0011E560(float,float);float func_0011EE68(LM*,float);
qword func_0011FD70(float,float,float);int func_0011EE30(LM*,float);
int func_001ED460(void*,qword,qword*);
int func_001ED350(void*,qword,qword,int,SEGMENT*);
void func_00120A00(qword,qword,qword,qword*,float*,float*);
}
struct VU_FLOAT{qword qw;};
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwOffset(qword base,qword v,const qword&g,U*scratch){scratch->q=g;qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g));return r;}
static inline qword QwFromMemWord(int n){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"rV"(n));return v;}
static inline qword QwAddScaled(qword base,qword v,VU_FLOAT g){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g.qw));return r;}

static inline void Closest(qword t,const SEGMENT*s,U&pt,float&d){func_00120A00(t,s->a,s->b,&pt.q,0,&d);}
static inline M4*VMat(LO*plo){return plo->pvt->pfnMat((LO*)((char*)plo+plo->pvt->d));}
extern "C" qword func_00182068(P*p,void*region,qword origin,float heading){
 U closest;LM first,second,selected;U point;SEGMENT segments[8];FLOW flow;
 TUNING*tuning;
 first=p->actor->first;second=p->actor->second;
 {float factor=func_002575C0(p->actor);first.low*=factor;first.high*=factor;second.low*=factor;second.high*=factor;}
 tuning=p->actor->tuning;
 func_00120B00(QwSub(VMat(&p->actor->lo)->r[3],origin),&flow.polarAngle,&flow.polarLength,0);
 float angle=heading+func_0011E560(func_0011E3B8(flow.polarAngle-heading),tuning->narrow);
 float length=func_0011EE68(&first,flow.polarLength);
 if(func_001ED460(region,QwAdd(origin,func_0011FD70(angle,length,0.0f)),&closest.q)){
  func_00120B00(QwSub(closest.q,origin),&flow.candidateAngle,&flow.candidateLength,0);
  if(__builtin_fabsf(func_0011E3B8(flow.candidateAngle-heading))<tuning->wide&&func_0011EE30(&second,flow.candidateLength))return closest.q;
 }
 qword best;U target;
 int mode;
 for(mode=0;mode<3;mode++){
  int count;float limit;
  switch(mode){
  case 0:selected=first;count=10;limit=tuning->narrow;break;
  case 1:selected=second;count=10;limit=tuning->wide;break;
  case 2:selected.low=0.0f;selected.high=second.high;count=15;limit=3.14159265f;break;
  }
  if(tuning->override==-1)limit=3.14159265f;
  float bestDistance=3.40282347e+38f;
  int index;
  for(index=0;index<count;index++){
   int k=0;
   qword direction=func_0011FD70(heading+((float)index/((count-1)*0.5f)*limit-limit),1.0f,0.0f);
   int hits=func_001ED350(region,QwOffset(origin,direction,QwFromMemWord(*(int*)&selected.low),&point),QwOffset(origin,direction,QwFromMemWord(*(int*)&selected.high),&point),8,segments);
   for(;k<hits;k++){
     SEGMENT*base=segments;
     Closest(target.q,&base[k],point,flow.distance);
     if(flow.distance<bestDistance){best=point.q;bestDistance=flow.distance;}
   }
  }
  if(bestDistance!=3.40282347e+38f)return best;
 }
 if(func_001ED460(region,origin,&closest.q))return closest.q;
 return origin;
}
