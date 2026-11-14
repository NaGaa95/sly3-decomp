// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* func_0024C288 (Sly 3: camera position via func_001F4A80 + vcall; based on the Sly 2 match): four-ray visibility of an actor from the selector's origin (p+0x20, the caller
 * func_00202540 raises it by 20). Collects the objects between the two points (func_0025CF18 with the func_0024C260 filter),
 * then casts rays from the origin to the actor's centre (pulled radius 0xE4 towards the viewer) and to that centre moved by
 * the radius along the camera's up row (D_002DDFA0[1]) and along the side direction up x view. Every ray that hits an object
 * counts: none -> state 1, all four -> state 2 (func_00202540 drops those), some -> state 3. No register pins.
 * What made it match: the actor position is a plain qword across the call (spilled to 0x70 by the compiler), the scale-by-radius
 * multiplies are in place on direction/up (so they wait for the cross product), the side vector's dot product names its
 * operand twice, and the case-4 constant is a variable set before the switch (the game has it in v1 in the beqz delay slot). */
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct VTE {short delta;short pad;void *pfn;};
struct POSO {char pad[0x10];qword up;char pad20[0x10];qword pos;};
struct LO {char pad0[0xC];VTE *vt;char pad10[0xC4];float radius;char padD8[0x20];int state;};
struct P {char pad20[0x20];qword position;char pad30[0x78];LO **ppcam;};
struct QUERY {int count;LO **objects;};
// Stack-scope object (sp+0): __10STACKSCOPE opens it, _$_10STACKSCOPE(this,2) frees the stack memory taken since.
struct FRAME {FRAME();~FRAME();};
extern "C" LO *func_001F4A80(LO *);
extern "C" int func_0024C260(void *,LO *);
extern "C" void func_0025CF18(void *,qword,qword,int (*)(void *,LO *),void *,int *,LO ***);
extern "C" LO *func_00165000(int,qword,qword,int,LO **,void *);
extern "C" char D_00475480[];
static inline POSO *Poso(LO *plo){VTE *e=&plo->vt[0x24];return ((POSO *(*)(void *))e->pfn)((char *)plo+e->delta);}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
// v / |v|: the dot product names v twice (the side vector's registers only match that way)
static inline qword Normalize(qword v)
{
    qword d,one,l,r;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(v),"j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(l):"j"(d));
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(l),"j"(v));
    return r;
}
// v *= k.x in place
#define SCALE_IN_PLACE(v,k) __asm__("vmulx.xyzw %0,%0,%1x":"+j"(v):"j"(k))
extern "C" void func_0024C288(P *p,LO *other)
{
    int cHit=0;
    unsigned i=0;
    LO *pcam=func_001F4A80(*p->ppcam);
    FRAME frame;
    V points[4],scale;
    QUERY query;
    float radius;
    V *point;
    qword origin=Poso(other)->pos;
    radius=other->radius;
    func_0025CF18(D_00475480,origin,p->position,func_0024C260,0,&query.count,&query.objects);
    {
        qword up=Poso(pcam)->up;
        qword direction=Normalize(Sub(p->position,origin));
        qword side,upk;
        register qword k asm("vf4"); /* pin: radius in vf4 (else it swaps with the position) */
        __asm__("qmtc2.ni %1,%0":"=j"(k):"r"(radius));
        upk=Scale(up,k);
        scale.q=k;
        side=Normalize(Cross(up,direction));
        SCALE_IN_PLACE(direction,scale.q);
        origin=Add(origin,direction);
        points[0].q=origin;
        points[1].q=Add(origin,upk);
        points[2].q=Sub(origin,upk);
        points[3].q=Add(origin,Scale(side,scale.q));
    }
    point=points;
    for(;i<4;++i){
        if(func_00165000(0,p->position,point->q,query.count,query.objects,0))++cHit;
        ++point;
    }
    {
        int cRay=4;
        switch(cHit){case 0:other->state=1;break;case 4:other->state=2;break;case 1:case 2:case 3:other->state=3;break;}
        i=cRay;
    }
}
