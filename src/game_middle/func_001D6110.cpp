// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Mover/follower state controller: switch from the current state to `next`.
// Leaving states -1/0/2/3 restores the group's default action; entering a state sets up its velocity, mode, timers or
// effect; afterwards the new state, its time stamp and (except for state 2) the state's animation entry are recorded.
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
union F{float value;int bits;};
struct VE{short delta,pad;void*fn;};
struct M4{U row[4];};struct M3{U row[3];};
struct PATH;struct ASEG;struct ASEGA;struct EFFECT;struct SOURCE;
struct ENT{ASEG*clip;int flags;int pad;};   // per-state animation table entry (12 bytes)
struct P{char pad0[12];VE*vt;char pad10[0x4C-0x10];void*group;char pad50[0x138-0x50];float low0,high0,low1,high1,lead;char pad14c[4];PATH*path;float parameter,phase;char pad15c[4];ENT aseg[4];char pad190[0x1A4-0x190];ASEGA*animation;char pad1c8[8];F speed;int oldMode;float heading;char pad1dc[4];M3 basis;float spin[3];float ratio;int state;float changed,randomDeadline,deadline;int amount;char pad234[12];U damageOffset;};
// copy-constructed wrapper: gcc keeps its register copy (the original has the extra `por a1,zero,v0` for the position)
struct VV{qword q;VV(const qword&v){q=v;}};
struct WORK{U first,second,direction,velocity,scalar;float angle,parameter;};
struct CLOCK{float t,dt;};
extern "C"{
 extern CLOCK D_0036BB98;extern U D_00317560,D_00317530;extern char D_00475480[],D_0036BD20[];
 void func_0028F068(P*,void*,int);void func_0028B1B0(P*,void*);void func_0028B188(P*,void*);
 float func_0011E940(float,float);void func_00120BA8(qword,float*,float*,float*);
 void func_001D6608(P*,float);void func_001D65A8(P*,float);
 void func_0022EA88(PATH*,qword,void*,U*,U*,float*,float*);
 float func_0022F3F8(PATH*);float func_0022DFD8(PATH*);P*func_001F4C40(void*,qword);
 EFFECT*func_002459F8(int);void func_00244F08(EFFECT*,SOURCE*);void func_00245000(EFFECT*,qword);
 qword func_001C9428(P*,P*,qword);void func_00171E50(void*,qword,int,int,P*);
 void func_00137588(ASEG*,P*,float,float,int,ASEGA**);
}
static inline void SetVelocity(P*p,qword q){VE&v=p->vt[40];((void(*)(void*,qword))v.fn)((char*)p+v.delta,q);}
static inline void SetZeroVelocity(P*p){SetVelocity(p,D_00317560.q);}
// gnu-2.9 as does not insert the mtc1 hazard nop, so the helpers below add it themselves
// broadcast a float into a VU register and keep the scratch store the original left in `home`
static inline qword SplatInto(float f,U*home){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));home->q=q;return q;}
static inline qword ScaleX(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
// length of a vector, in two steps (sum of squares, then sqrt) so the stores/loads of the callers can sit between them
static inline qword LengthV(qword v){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;}
static inline float FloatOf(qword a){float f;int t;__asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0\n\tnop":"=f"(f),"=&r"(t):"j"(a));return f;}
// v * (1/n.x); the "memory" clobbers (here and on LEN1M/LEN2M) keep the surrounding loads/stores in source order
static inline qword DivBy(qword v,qword n){qword r;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(n),"j"(v):"memory");return r;}
static inline qword SplatBits(int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
#define LEN1M(d,v) __asm__("vmul.xyz %0,%1,%1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf2,%0z":"=j"(d):"j"(v):"memory","vf2")
#define LEN2M(d) __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d): :"memory")
// world position: row 3 of the matrix returned by method 36
static inline qword Position(P*p){VE&v=p->vt[36];return ((M4*(*)(void*))v.fn)((char*)p+v.delta)->row[3].q;}
static inline void Call(P*p,int index){VE&v=p->vt[index];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetMode(P*p){VE&v=p->vt[51];((void(*)(void*,int))v.fn)((char*)p+v.delta,4);}
static inline M4*GetMatrix(P*p){VE&v=p->vt[36];return ((M4*(*)(void*))v.fn)((char*)p+v.delta);}

extern "C" void func_001D6110(P*p,int next){
 int old=p->state;if(old==next)return;WORK w;
 switch(old){case -1:case 0:case 2:case 3:func_0028F068(p,p->group,p->oldMode);func_0028B1B0(p,p->group);break;}
 switch(next){
 case 0:
  SetVelocity(p,D_00317560.q);func_0028B188(p,p->group);{float now=D_0036BB98.t;p->randomDeadline=now+func_0011E940(p->low0,p->high0);}break;
 case 1:
  SetMode(p);{float now=D_0036BB98.t;p->randomDeadline=now+func_0011E940(p->low1,p->high1);}break;
 case 2:{
  p->phase=-p->phase;float negative=-1.0f;M4*m=GetMatrix(p);
  qword row=m->row[0].q;qword factor=SplatInto(negative,&w.first);qword scaled=ScaleX(row,factor);
  func_00120BA8(scaled,&w.angle,0,0);func_001D6608(p,w.angle);SetZeroVelocity(p);func_0028F068(p,p->group,1);func_0028B1B0(p,p->group);break;
 }
 case 3:
  SetZeroVelocity(p);func_001D65A8(p,p->ratio+p->ratio);
  func_0028F068(p,p->group,1);func_0028B1B0(p,p->group);break;
 case 4:{
  VV pos(Position(p));w.first.q=pos.q;
  if(p->path){
   func_0022EA88(p->path,w.first.q,0,&w.second,0,&p->parameter,&w.parameter);
   float phase=func_0022F3F8(p->path);
   qword delta=Sub(w.first.q,w.second.q);
   float speed=p->speed.value;
   float travel=FloatOf(LengthV(delta));
   p->phase=phase;
   travel/=speed;
   float end=func_0022DFD8(p->path);
   p->deadline=D_0036BB98.t+travel+(end-w.parameter)/p->speed.value-p->lead;
  }else{
   P*near=func_001F4C40(D_00475480,w.first.q);w.second=w.first;w.first.q=Position(near);p->deadline=D_0036BB98.t+2.0f;
  }
  qword ff=w.first.q;qword ss=w.second.q;qword gap=Sub(ss,ff);
  w.direction.q=gap;w.direction.i[2]=0;
  qword point=w.direction.q;
  qword norm;LEN1M(norm,point);
  qword fallback=D_00317530.q;LEN2M(norm);float length;qword direction;
  register int lengthBits __asm__("$3"); // register pin: the length bits go through $v1, $v0 keeps the fallback vector
  __asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0\n\tnop" : "=f"(length), "=&r"(lengthBits) : "j"(norm));
  if(length<0.0001f)direction=fallback;else direction=DivBy(point,norm);
  qword factor=SplatBits(p->speed.bits);
  w.scalar.q=factor;
  qword velocity=ScaleX(direction,factor);
  w.velocity.q=velocity;SetVelocity(p,velocity);SetMode(p);break;
 }
 case 5:{
  EFFECT*e=func_002459F8(0x14);func_00244F08(e,0);func_00245000(e,Position(p));
  func_00171E50(D_0036BD20,func_001C9428(p,0,p->damageOffset.q),p->amount,-100,p);Call(p,9);break;
 }
 }
 p->state=next;p->changed=D_0036BB98.t;
 if(next!=2){
  func_00137588(p->aseg[next].clip,p,0.0f,1.0f,p->aseg[next].flags|1,&p->animation);
 }
}
