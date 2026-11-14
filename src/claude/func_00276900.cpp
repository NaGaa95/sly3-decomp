// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00276900: PosEyeCut - Sly 3 form of Sly 2 PosEyeCut__FP8CPFOLLOWG9VU_VECTORT1P6VECTOR (0x223A70).
// Sly 3: CTX scope (explicit __3CTX/_$_3CTX on the WORK slot at 0x40), the object position comes from vtable slot 36 (+0x30),
// the eye squish takes an extra int arg 1, the camera is p->cm (radius 0x140), FLT_MAX/0 rodata is a static table;
// the start angle (0) doubles as the first interval gap, the later gap is the literal 0. One pin: bestCost in f21.
// No instruction asm (the Sly 2 StoreVF sqc2 became a plain store).
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct SO;
struct N;
struct CMX {char pad[0x140];float radius;};
struct VTE {short delta,pad;void *(*fn)(void *);};
struct OBJ {char pad[0xC];VTE *vt;};
struct S {CMX *cm;char pad4[0x24];OBJ *object;char pad2C[0xB0-0x2C];int state;};
struct CAMERA {char pad[0x48];float radius;};
struct WORLD;
extern WORLD D_00475480;
extern "C" {
void *__3CTX(void *);
void _$_3CTX(void *,int);
int func_00167578(void *,SO *);
void func_0025CF18(WORLD *,qword,qword,int (*)(void *,SO *),void *,int *,SO ***);
qword FindCmClosestClearPos(int,SO **,qword,float) asm("func_001670A8");
int FFindCmClearInterval(int count,SO **objects,qword origin,qword endpoint,float gap,float *low,float *high) asm("func_00166F08");
float GCmCutWeight(void *,qword,qword,N *) asm("func_002768A0");
qword SquishCmEye(CMX *,int,SO **,int,float (*)(void *,qword,qword,N *),qword,qword,float,float) asm("func_001672A0");
void func_0011EF08(qword,float *,float *,float *) asm("func_00120B00");
qword func_0011E1A0(float,float,float) asm("func_0011FD70");
}
struct MARK {char pad[0x10];};
static inline qword Pos(OBJ *o){VTE *v=&o->vt[36];return *(qword *)((char *)v->fn((char *)o+v->delta)+0x30);}
static const float s_aflt[2]={3.402823466e+38f,0.0f};
struct WORK {V minimum,maximum,origin,candidate;MARK mark;V offset,rayEnd,best,scalar;int count;SO **objects;float low,high,phase,radius,height;};
static inline qword Min(qword a,qword b){qword r;__asm__("vmini.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Max(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ToVF(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarHome(V &home,float value){home.q=Scalar(value);return home.q;}
static inline qword Blend(qword a,qword b,qword left,qword right){__asm__("vmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(a):"j"(b),"j"(left),"j"(right));return a;}
static inline qword BlendToRight(qword a,qword b,qword left,qword right){__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%0,%3x":"+j"(b):"j"(a),"j"(left),"j"(right));return b;}
static inline float Abs(float f){return __builtin_fabsf(f);}
extern "C" void func_00276900(S *p,qword begin,qword end,qword *out){
    OBJ *object=p->object;
    WORK w;
    __3CTX(&w.mark);
    qword final;
    float angle=0.0f;
    w.minimum.q=Min(begin,Min(end,Pos(object)));
    w.maximum.q=Max(begin,Max(end,Pos(object)));
    func_0025CF18(&D_00475480,w.minimum.q,w.maximum.q,func_00167578,0,&w.count,&w.objects);
    int count=w.count; SO **objects=w.objects;
    w.origin.q=FindCmClosestClearPos(count,objects,Pos(object),500.0f);
    FFindCmClearInterval(w.count,w.objects,w.origin.q,end,angle,&w.low,&w.high);
    if(w.high<1.0f){
        p->state=4;
        func_0011EF08(Sub(end,begin),&w.phase,&w.radius,&w.height);
        register float bestCost __asm__("$f21")=s_aflt[0]; // pin: bestCost gets f21 (angle f20)
        do{
            qword off=func_0011E1A0(w.phase+angle,w.radius,w.height);
            w.offset.q=off;
            w.rayEnd.q=Add(begin,off);
            FFindCmClearInterval(w.count,w.objects,w.origin.q,w.rayEnd.q,0.0f,&w.low,&w.high);
            float cost=(1.25f-w.high)*(Abs(angle)+0.47123894f);
            if(cost<bestCost){
                float left=1.0f-w.high;
                bestCost=cost;
                qword a=ScalarHome(w.scalar,left);
                qword right=ScalarHome(w.scalar,w.high);
                w.best.q=Blend(w.origin.q,w.rayEnd.q,a,right);
            }
            float next=-angle;
            if(angle<=0.0f)next+=0.28559935f;
            angle=next;
            if(bestCost<(Abs(next)+0.47123894f)*0.25f)break;
        }while(angle<3.1415927f);
        w.candidate.q=w.best.q;
    }else w.candidate.q=end;
    final=ToVF(SquishCmEye(p->cm,w.count,w.objects,1,GCmCutWeight,w.candidate.q,w.candidate.q,p->cm->radius,p->cm->radius));
    FFindCmClearInterval(w.count,w.objects,w.candidate.q,final,0.0f,&w.low,&w.high);
    if(w.high!=1.0f){
        float u=(w.low+w.high)*0.5f;
        qword left=ScalarHome(w.offset,1.0f-u);
        qword right=ScalarHome(w.offset,u);
        final=BlendToRight(w.candidate.q,final,left,right);
    }
    *out=final;
    _$_3CTX(&w.mark,2);
}
