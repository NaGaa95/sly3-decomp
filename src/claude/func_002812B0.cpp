// Reference: Sly 2 src/hand/func_002297F8.cpp; target Sly 3 0x002812B0.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Resolve one contact between two physics objects: spring push, friction impulses (linear and
// angular), restoring torque, and the water-splash / emitter-clear effects.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {M3 basis;qword position;};
struct COEF {float f[3];};
struct O;
struct VE {short delta,pad;qword (*get)(void *);};
struct NODE {char pad[0x98];short kind;};
struct CONSTRAINT {qword direction;int kind;};
struct PHYS {char pad[0x80];V direction;char pad90[0x20];CONSTRAINT constraint;float mass,spring,friction;};
struct STATE {V minimum,maximum;};
struct EMITTER;
struct WATER;
struct XF {M3 basis;qword position;};
struct XE {short delta,pad;XF *(*get)(void *);};
struct O {char pad[0xC];VE *vt;char pad10[0x38];NODE *body,*rotation,*motion;char pad54[0x84];PHYS *physics;STATE *state;char padE0[0x70];EMITTER *emitter;};
union PHASE {V vectors[3];M3 basis;};
union AXIS {COEF coefficients;V vector;};
struct WORK {V point,normal,velocity;PHASE phase;AXIS axis;V angularNormal,angularTangent,scalar;float angle;};
extern qword D_00317560;
extern M3 D_00317490;
extern COEF D_00329560,D_00329570;
extern float D_0036BB9C;
extern "C" {
float func_00280EA8(O *,O *,qword *,qword *);
int func_0011E9F0(float,float,float);
qword func_00244418(CONSTRAINT *,NODE *,qword);
void func_00244828(O *,qword);
void func_00280598(O *,qword,qword *,qword *);
float func_0011FE60(qword,qword,qword *,qword *);
int func_0028F048(int);
void func_0023F180(O *,qword,const COEF *,qword,const COEF *);
void func_0023EFA0(O *,const M3 *,const COEF *,qword,const COEF *);
void func_0011CCF8(const M3 *,M3 *,M3 *);
void DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(const M3 *,float *,qword *);
void func_00244890(O *,qword);
void func_00178278(O *,WATER *,float,qword,qword,float,float);
int func_0013B500(O *,int);
void func_00244CA8(EMITTER *,float);
void func_002BBCD8(EMITTER **,EMITTER *);
}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline bool Near(qword a,qword b,float epsilon){return func_0011E9F0(X(a),X(b),epsilon)&&func_0011E9F0(Y(a),Y(b),epsilon)&&func_0011E9F0(Z(a),Z(b),epsilon);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline XF *Xf(O *o){VE *v=o->vt;return ((XE *)v)[36].get((char *)o+v[36].delta);}
static inline qword Get(O *o,int slot){VE *v=o->vt;return v[slot].get((char *)o+v[slot].delta);}
static inline qword Sub(qword a,qword b){qword r;asm("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"0"(b));return r;}
static inline qword AddNormal(qword motion,const V &projection){qword r;asm("vadd.xyzw %0,%1,%2":"=j"(r):"0"(motion),"j"(projection.q));return r;}
static inline qword AddTangent(qword motion,const V &projection){qword r;asm("vadd.xyzw %0,%1,%2":"=j"(r):"0"(motion),"j"(projection.q));return r;}
static inline qword NegativeAngular(qword angular,float sign,qword &scalar){qword factor;asm("qmtc2.ni %1,%0":"=j"(factor):"r"(sign));scalar=factor;return Scale(angular,factor);}
// The coefficient tables are indexed directly (not through a pointer) so each loop forms its own address.
#define GAIN2(G,amount,friction) {for(i=0;i<3;i++)w.axis.coefficients.f[i]=G.f[i]*amount*friction;}
#define GAIN1(G,friction) {for(i=0;i<3;i++)w.axis.coefficients.f[i]=G.f[i]*friction;}
static inline void Zero(V &v,float zero){v.f[0]=v.f[1]=v.f[2]=zero;}
static inline void Clear(EMITTER **emitter){if(emitter&&*emitter){func_00244CA8(*emitter,0.0f);func_002BBCD8(emitter,0);}}
extern "C" void func_002812B0(O *a,O *b){
 WORK w;
 int i;
 float span=func_00280EA8(b,a,&w.point.q,&w.normal.q);
 float epsilon=0.0001f;
 if(span<epsilon)return;
 float spring=Near(D_00317560,a->physics->direction.q,epsilon)?0.0f:a->physics->spring*b->physics->spring;
 float friction=a->physics->friction*b->physics->friction;
 float factor;
 if(spring!=0.0f){
  qword k=Scalar(-spring*span);w.velocity.q=k;
  func_00244828(a,func_00244418(&a->physics->constraint,a->motion,Scale(a->physics->direction.q,k)));
 }
 if(friction!=0.0f){
  func_00280598(b,Xf(a)->position,&w.velocity.q,&w.phase.vectors[0].q);
  qword linear=Get(a,38);qword relative=Sub(w.velocity.q,linear);
  float dot=func_0011FE60(relative,w.normal.q,&w.phase.vectors[1].q,&w.phase.vectors[2].q);
  if(span==1.0f||0.0f<dot)factor=1.0f;else factor=span*0.5f+0.5f;
  if(func_0028F048(a->body->kind)){
   GAIN2(D_00329560,factor,friction);
   func_0023F180(a,D_00317560,0,AddNormal(linear,w.phase.vectors[1]),&w.axis.coefficients);
   GAIN2(D_00329560,span,friction);
   func_0023F180(a,D_00317560,0,AddTangent(linear,w.phase.vectors[2]),&w.axis.coefficients);
  }
  if(func_0028F048(a->rotation->kind)){
   qword angular=Get(a,39);
   qword k;
   qword negative=NegativeAngular(angular,-1.0f,k);
   w.scalar.q=k;func_0011FE60(negative,w.normal.q,&w.angularNormal.q,&w.angularTangent.q);
   GAIN2(D_00329570,span,friction);
   func_0023EFA0(a,&D_00317490,0,AddNormal(angular,w.angularNormal),&w.axis.coefficients);
   GAIN1(D_00329570,friction);
   func_0023EFA0(a,&D_00317490,0,AddTangent(angular,w.angularTangent),&w.axis.coefficients);
  }
 }
 else Zero(w.velocity,0.0f);
 if(spring!=0.0f){
  func_0011CCF8(&Xf(a)->basis,&w.phase.basis,0);
  DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(&w.phase.basis,&w.angle,&w.axis.vector.q);
  float gain=spring*3.0f;qword k=Scalar(w.angle*gain*span);
  qword rotation=Scale(w.axis.vector.q,k);w.angularNormal.q=k;
  func_00244890(a,rotation);
 }
 if(0.0f<span&&span<1.0f&&0.9f<w.normal.f[2]){
  float radius=((a->state->maximum.f[0]-a->state->minimum.f[0])+(a->state->maximum.f[1]-a->state->minimum.f[1]))*0.25f;
  func_00178278(a,(WATER *)b,D_0036BB9C,w.velocity.q,w.point.q,0.1f,radius);
 }
 else if(func_0013B500(a,0x31))Clear(&a->emitter);
}

