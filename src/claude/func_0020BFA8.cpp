// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0020BFA8 (agent A92): MoveRip - Sly 3 form of Sly 2 MoveRip__FP4RIPN (0x1CF0A0, src/hand/func_001CF0A0.cpp).
// Spin the rip by its angular velocity (damped by gE0*dt), then step its position with the particle system matrix.
// Sly 2's instruction asm (clock lui/lw, basis sqc2 stores) is plain C here; the extra "j"(a) on AddScaled is
// allocation-only. One pin: the third Multiply row input in vf1.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M3 {U r[3];M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};struct M4 {qword a,b,c,d;};
struct PHYS {qword accel,axis;float rate,scale;};
struct S {char pad[0x40];M3 mat;qword pos,prev,vel;PHYS phys;qword omega;float gE0,gE4;};
extern struct CLOCK {float time;union{float dt;int dtbits;};} g_clock;
extern "C" {
int func_0020BF18(qword);int func_0020BED0(qword);int func_0020BF60(qword);
M3*BuildRotateMatrixAxis(M3*,qword,float) asm("func_0011C8C0");M4 *UpdatePsys(M4*,PHYS*) asm("func_00179CC0");
void func_0020BFA8(S*);
}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Sq(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Sqrt(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Float(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
struct R3 {U r[3];};
struct MATH {U first,second;R3 scratch;};
union SHARED {MATH math;M4 matrix;};
struct WORK {SHARED shared;R3 rotation,product;};
static inline qword Broadcast(U*storage,float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));storage->q=r;return storage->q;}
static inline qword BroadcastBits(U*storage,int f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));storage->q=r;return storage->q;}
static inline qword Normalize(qword a,float f,U*storage){qword r,l=Broadcast(storage,f);__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(l),"j"(a));return r;}
static inline void Multiply(R3*scratch,R3*out,const R3*a,const M3&b){
 qword row0=b.r[0].q;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(row0):"j"(a->r[0].q),"j"(a->r[1].q),"j"(a->r[2].q),"j"(b.r[0].q));
 scratch->r[0].q=row0;out->r[0]=scratch->r[0];
 qword row1=b.r[1].q;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(row1):"j"(a->r[0].q),"j"(a->r[1].q),"j"(a->r[2].q),"j"(b.r[1].q));
 scratch->r[1].q=row1;out->r[1]=scratch->r[1];
 register qword input2 __asm__("vf1")=b.r[2].q; // pin: third row input in vf1
 qword row2=a->r[0].q;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(row2):"j"(a->r[0].q),"j"(a->r[1].q),"j"(a->r[2].q),"j"(input2));
 out->r[2].q=row2;scratch->r[2]=out->r[2];
}
static inline qword Point(const M4 &m,qword a){qword r=m.a;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m.a),"j"(m.b),"j"(m.c),"j"(m.d),"j"(a));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s),"j"(a));return r;}

// name: SafeHouse port (MoveRip)
void func_0020BFA8(S*p){
 WORK w;
 if(!func_0020BF18(p->omega)) {
  qword omega=Scale(p->omega,Broadcast(&w.shared.math.first,p->gE0*g_clock.dt+1.0f));
  p->omega=omega;
  float length=Float(Sqrt(Sq(omega)));
  if(0.0001f<length){
   w.shared.math.first.q=Normalize(omega,length,&w.shared.math.second);
   BuildRotateMatrixAxis((M3*)&w.rotation,w.shared.math.first.q,length*g_clock.dt);
   Multiply(&w.shared.math.scratch,&w.product,&w.rotation,p->mat);
   p->mat.r[0]=w.product.r[0];p->mat.r[1]=w.product.r[1];p->mat.r[2]=w.shared.math.scratch.r[2];
  }
 }
 p->prev=p->pos;
 int moving=0;
 if(!func_0020BED0(p->vel) || !func_0020BF60(p->phys.accel))moving=1;
 if(moving){
  UpdatePsys(&w.shared.matrix,&p->phys);
  qword v=Point(w.shared.matrix,p->vel);
  p->vel=v;
  p->pos=AddScaled(p->pos,v,BroadcastBits(&w.shared.math.first,g_clock.dtbits));
 }
}

