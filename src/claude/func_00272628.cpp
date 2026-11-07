// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// func_00272628: UpdateJtThrowArc (Sly 2 func_0021FB70, src/hand/func_0021FB70.cpp in the Sly 2 decomp). Ported to
// Sly 3: the hero's position comes from its Matrix() virtual (slot 36), an aim override (f13C: uFar / launch elevation
// given directly), no power-up scaling of tPredict (always 1.35), the flight-time rate limit only when fUpdateBlends,
// the heading error from the dpos heading (func_001205C8) less atan2 of the hero matrix's x row, and uFar's blend rate
// limit skipped with the aim override.
typedef int qword __attribute__((mode(TI)));

union V {qword q;float f[4];int n[4];};
struct M3 {V r[3];};
struct M4 {M3 basis;V position;};
// The current stack-allocation scope (out of line: __3CTX / _$_3CTX)
struct CTX {CTX();~CTX();};
struct SW;
struct SO;
struct ASEGBL;
#define VF1(n) virtual void V##n();
class LO {
public:
 int hdr[3];
 VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7) VF1(8) VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16)
 VF1(17) VF1(18) VF1(19) VF1(20) VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31) VF1(32)
 VF1(33) VF1(34) VF1(35)
 virtual M4 *Matrix();                       // 36
};
struct GRAVITY {char unk0[0x80];V vAccel;};
struct CARRIED {char unk0[0xD8];GRAVITY *pgravity;void *pvFilter;};
struct ARCFRAME {float t,gValid,s;M4 mat;};
struct MARKER {char unk0[0x13C];int cframe;ARCFRAME *aframe;};
struct LM {float gMin,gMax;};
struct CLQ {float g0,g1,g2;};
struct BL {float gWeight;ASEGBL *pasegbl;int unk8;};
struct JTTHROW {
 LO *pstepplayer;char unk4[0xC];CARRIED *ploCarried;char unk14[4];float radTurnAim;LM lmAim;float tPredict;
 char unk28[0x40];BL ablB[4];ASEGBL *pasegblB;char unk9C[8];BL ablC[2];ASEGBL *pasegblC;
 char unkC0[0x20];V vLaunchLocal,posHold,vLaunch;char unk110[0x2C];int fAimFixed;float uFarFixed,gFixed;MARKER *ploMarker;float tFlight;
};
struct HIT {V pos;char unk10[0x50];};
struct CLOCK {float t,dt;};
extern SW D_00475480;
extern CLOCK g_clock;
extern const CLQ D_00329050;                   // the launch elevation over the aim distance
extern V D_00317550;                           // (0, 0, 1)
struct VU_VECTOR {qword q;VU_VECTOR(){}VU_VECTOR(qword qw){q=qw;}};
struct VU_FLOAT {qword q;};
extern "C" {
 qword func_001C9428(LO *,LO *,qword);          // ConvertLoPos
 qword func_00212480(qword,qword,qword,float);  // CalculateLaunchVelocity
 void func_0025CF18(SW *,qword,qword,int (*)(void *,SO *),void *,int *,SO ***); // FindSwObjectsInBox
 int func_002725D0(void *,SO *);
 SO *func_00165000(int,qword,qword,int,SO **,HIT *);
 int func_0011EA28(float,float,float,float *);  // CSolveQuadratic
 M3 *func_0011CBF0(M3 *,qword,qword);           // BuildLookAtMatrix
 V *func_002BA818(V *,qword);
 void func_0026EC80(MARKER *,qword);
 float func_001205C8(VU_FLOAT);
 float func_002A3EE8(float,float);              // atan2f
 float func_0011E3B8(float);                    // RadNormalize
 void func_00148938(ASEGBL *);
}
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.q):"r"(g));return v;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline VU_VECTOR VuSub(VU_VECTOR a,VU_VECTOR b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a.q),"j"(b.q));return VU_VECTOR(r);}
static inline VU_FLOAT VfSub(qword a,qword b){VU_FLOAT r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r.q):"j"(a),"j"(b));return r;}
static inline qword QwMin(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwMax(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float GFromVf(qword v){float g;__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(v));return g;}
static inline float GZOfQw(qword v){float g;__asm__("pextuw %0,$zero,%1":"=r"(g):"r"(v));return g;}
static inline float GLengthXY(qword v){
 __asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return GFromVf(v);
}
static inline float GLength(VU_VECTOR w){qword v=w.q;qword one;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(v));return GFromVf(v);
}
static inline qword QwBallistic(const qword &pos,const qword &a,const qword &v,VU_FLOAT t,VU_FLOAT t2){qword r;
 __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(r):"j"(pos),"j"(v),"j"(t.q),"j"(a),"j"(t2.q));return r;
}
static inline qword PosOnArc(const qword &pos,const qword &a,const qword &v,float t,float gHalf){return QwBallistic(pos,a,v,VuFloat(t),VuFloat(t*(t*gHalf)));}
static inline qword QwCombine(qword a,qword b,VU_FLOAT g0,VU_FLOAT g1){qword r;
 __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(g0.q),"j"(b),"j"(g1.q));return r;
}
static inline float GClamp(float g,float gMin,float gMax){if(g<gMin)return gMin;if(gMax<g)return gMax;return g;}
static inline float GMax(float g0,float g1){return g0<g1?g1:g0;}
static inline float GFromClq(const CLQ &clq,float x){return clq.g0+x*(clq.g1+x*clq.g2);}

extern "C" void func_00272628(JTTHROW *pjtthrow,int fUpdateBlends)
{
 qword posLaunch=func_001C9428(pjtthrow->pstepplayer,0,pjtthrow->vLaunchLocal.q);
 qword posHold=pjtthrow->posHold.q;
 qword vAccel=pjtthrow->ploCarried->pgravity->vAccel.q;
 qword posHero=pjtthrow->pstepplayer->Matrix()->position.q;
 float sAim=GLengthXY(QwSub(posHold,posHero));
 float uFar,gLaunch;
 if(pjtthrow->fAimFixed){uFar=pjtthrow->uFarFixed;gLaunch=pjtthrow->gFixed;}
 else{
  uFar=GClamp((sAim-pjtthrow->lmAim.gMin)/(pjtthrow->lmAim.gMax-pjtthrow->lmAim.gMin),0.0f,1.0f);
  gLaunch=GFromClq(D_00329050,uFar);
 }
 qword vLaunch=func_00212480(posLaunch,pjtthrow->posHold.q,vAccel,gLaunch);
 float tApex=GMax(-GZOfQw(vLaunch)/GZOfQw(vAccel),0.0f);
 qword posApex=PosOnArc(posLaunch,vAccel,vLaunch,tApex,0.5f);
 float t=pjtthrow->tPredict;
 t=t*1.35f;
 qword posEnd=PosOnArc(posLaunch,vAccel,vLaunch,t,0.5f);
 CTX ctx;
 qword posMin=QwMin(posApex,posEnd);
 qword posMax=QwMax(posApex,posEnd);
 posMax=QwMax(posLaunch,posMax);
 posMin=QwMin(posLaunch,posMin);
 int cso;SO **apso;
 func_0025CF18(&D_00475480,posMin,posMax,func_002725D0,pjtthrow->ploCarried->pvFilter,&cso,&apso);
 pjtthrow->vLaunch.q=vLaunch;
 float dt=t*0.034482758f;
 V apos[30];
 qword posPrev=posLaunch;
 unsigned i;
 for(i=1;i<29;i++){
  t=(float)(int)i*dt;
  qword pos=PosOnArc(posLaunch,vAccel,vLaunch,t,0.5f);
  HIT hit;
  if(func_00165000(1,posPrev,pos,cso,apso,&hit)){
   V at;
   int ct=func_0011EA28(GZOfQw(vAccel)*0.5f,GZOfQw(vLaunch),GZOfQw(posLaunch)-hit.pos.f[2],at.f);
   float tBest=0.0f,sBest=3.40282347e+38f;
   for(int it=0;it<ct;it++){
    float tRoot=at.f[it];
    if(tRoot<0.0f)continue;
    qword posRoot=PosOnArc(posLaunch,vAccel,vLaunch,tRoot,0.5f);
    float s=GLength(VuSub(posRoot,hit.pos.q));
    if(s<sBest){sBest=s;tBest=tRoot;}
   }
   t=tBest;
   break;
  }
  posPrev=pos;
 }
 if(fUpdateBlends){
  float dtMax=3.0f*g_clock.dt;
  pjtthrow->tFlight=GClamp(t,pjtthrow->tFlight-dtMax,pjtthrow->tFlight+dtMax);
 }else pjtthrow->tFlight=t;
 t=pjtthrow->tFlight;
 i=0;
 for(;;){
  if(t<0.1f)break;
  (apos+i)->q=PosOnArc(posLaunch,vAccel,vLaunch,t,0.5f);
  if(++i>=29)break;
  t=pjtthrow->tFlight-(float)(int)i*dt;
 }
 (apos+i)->q=posLaunch;
 int cpos=i+1;
 if(pjtthrow->ploMarker){
  ARCFRAME *pframe=pjtthrow->ploMarker->aframe+pjtthrow->ploMarker->cframe;
  qword posBefore=QwCombine(apos[0].q,apos[1].q,VuFloat(2.0f),VuFloat(-1.0f));
  V *ppos=apos;
  M4 mat;M3 matRot;
  for(int iframe=0;iframe<pjtthrow->ploMarker->cframe;iframe++){
   pframe--;
   if(iframe<cpos){
    V *pposCur=ppos++;
    qword pos=pposCur->q;
    qword dpos=QwSub(pos,posBefore);
    func_0011CBF0(&matRot,dpos,D_00317550.q);
    M4 *pmat=&mat;
    func_002BA818(&mat.position,pos);
    pmat->basis=matRot;
    posBefore=pos;
    mat.basis.r[2].n[3]=0;
    mat.basis.r[1].n[3]=0;
    mat.basis.r[0].n[3]=0;
    pmat->position.f[3]=1.0f;
    pframe->gValid=1.0f;
   }else pframe->gValid=0.0f;
   pframe->t=g_clock.t;
   pframe->s=0.0f;
   pframe->mat=mat;
  }
  func_0026EC80(pjtthrow->ploMarker,posLaunch);
 }
 qword posAim=pjtthrow->posHold.q;
 qword posHeroNow=pjtthrow->pstepplayer->Matrix()->position.q;
 float rad=func_001205C8(VfSub(posAim,posHeroNow));
 M4 *pmHero=pjtthrow->pstepplayer->Matrix();
 float radHero=func_002A3EE8(pmHero->basis.r[0].f[1],pmHero->basis.r[0].f[0]);
 rad=func_0011E3B8(rad-radHero);
 float uTurn=GClamp(rad/pjtthrow->radTurnAim,-1.0f,1.0f)*0.5f+0.5f;
 if(fUpdateBlends){
  float uFarOld=pjtthrow->ablC[1].gWeight,uTurnOld;
  if(uFarOld>0.5f)uTurnOld=pjtthrow->ablB[3].gWeight/uFarOld;
  else uTurnOld=pjtthrow->ablB[1].gWeight/(1.0f-uFarOld);
  float du=g_clock.dt*2.0f;
  if(!pjtthrow->fAimFixed)uFar=GClamp(uFar,uFarOld-du,uFarOld+du);
  uTurn=GClamp(uTurn,uTurnOld-du,uTurnOld+du);
 }
 float uTurnOpp=1.0f-uTurn;
 float uNear=1.0f-uFar;
 pjtthrow->ablB[0].gWeight=uTurnOpp*uNear;
 pjtthrow->ablB[1].gWeight=uTurn*uNear;
 pjtthrow->ablB[2].gWeight=uTurnOpp*uFar;
 pjtthrow->ablB[3].gWeight=uTurn*uFar;
 func_00148938(pjtthrow->pasegblB);
 pjtthrow->ablC[0].gWeight=uNear;
 pjtthrow->ablC[1].gWeight=uFar;
 func_00148938(pjtthrow->pasegblC);
}
