// Reference: Sly 2 src/hand/func_001F9410.cpp; target Sly 3 0x00243020.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00243020: solve the contacts of a group of touching objects (Sly 1 SolveSwGroup).
// Builds a DZG over the contacts (func_001585D8), turns every contact into a DZ row with its limits,
// sets each row's target (bounce or separating speed), solves (func_00175D70) and applies the
// impulses (func_00176070), then tells the objects (vtable callbacks 65/66/67).
// Args: (game, flags, objectCount, objects, contactCount, contacts). flags&1 = resting contacts,
// flags&4 = position pass first (returns early when flags == 4).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
typedef union U U;
typedef union FLOAT FLOAT;
typedef struct XP XP;
typedef struct VT VT;
typedef struct BODY BODY;
typedef struct MOTION MOTION;
typedef struct P P;
typedef struct DLE DLE;
typedef struct DL DL;
typedef struct DZ DZ;
typedef struct DZS DZS;
typedef struct DZG DZG;
typedef struct CLOCK CLOCK;
typedef struct GAME GAME;
typedef struct FRAME FRAME;

struct XP;
struct VT {short delta,unused;void (*function)(void *);};
struct BODY {char pad0[0x98];short kind;char pad9A[0x16];U velocity;};
struct MOTION {char pad0[0x60];U linear,angular;};
struct P {char pad0[0xC];VT *vtable;char pad10[0x48-0x10];BODY *first,*second;char pad50[0xD8-0x50];MOTION *motion;};
struct XP {char pad0[0x80];U normal;float value;int unused94;float elasticity;int kind;float start,end;int index;int unusedAC;U velocity;};
struct DLE {void *next,*previous;};
struct DL {void *first,*last;int offset;};
union FLOAT {float value;int bits;};
struct DZ {int kind;float lower,upper,value;FLOAT target;int unused14;float *coefficients;int flags;DLE link;};
struct DZS {char pad0[0x40];U normal;XP *source;float *coefficients;char pad58[8];};
struct DZG {int capacity,count;DZ *rows;DL solved,pending,unused,active;int solvedCount;float *matrix,*inverse,*temporary,*results;int contactCount;XP **contacts;int objectCount;P **objects;DZS *states;};
struct CLOCK {float time,dt;};
struct GAME;
struct FRAME;
extern CLOCK g_clock;
extern GAME D_00475480;
struct FRAME {int c[4];};
FRAME *__3CTX(FRAME *);
void _$_3CTX(FRAME *,int);
DZG *func_001757D0(DZG *,int,XP **,int,P **);
void func_001758A0(DZG *,DZ *,DZS *);
void func_00175BD8(DZG *,int);
void func_00175870(DZG *,int);
void func_00176070(DZG *,float,float);
void func_0011B3F8(DZG *);
void RecalcSwXpPos(GAME *,int,XP **) asm("func_001CBAF0");
void RecalcSwXpMovement(GAME *,int,XP **) asm("func_001CBC30");
float GRandInRange(float,float) asm("func_0011E940");
void func_00175D70(DZG *,int);
void func_00243860(P *);
// Stack frame mark: ctor 0x1AE478, dtor 0x1AE4A0 (called with the 2.95 in-charge flag 2).
// Sly 3: the group is torn down by func_00175870(&group, 2) (a destructor called with the in-charge flag).

#define FLT_MAX 3.40282347e+38f

// store the x lane of a VU dot product to memory (lane helper, like Dot's mtc1 form)
static inline void DotQStore(qword a,qword b,float *d){qword one;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=j"(one):"j"(b));__asm__("sw %1,%0":"=m"(*d):"r"(a));}
static inline float Dot(qword a,qword b){qword one;float f;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=j"(one):"j"(b));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
// LengthSquaredNM: same without the memory clobber (lets the p->motion load schedule into the asm stall).
// "memory": the game re-reads p->second after this dot product.
static inline float LengthSquared(qword v){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one): :"memory");__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline float LengthSquaredNM(qword v){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline float Sqrt(float f){float r;__asm__ volatile("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float ClockDt(void){return g_clock.dt;}
static inline void Callback(P *p,int slot){VT *vt=p->vtable;vt[slot].function((char *)p+vt[slot].delta);}

void func_00243020(GAME *game,int flags,int objectCount,P **objects,int contactCount,XP **contacts)
{
    FRAME frame;
    XP *contact;DZ *row;int i;
    DZG group;
    float maximum;
    int fResting;
    int j;
    float magnitude;
    int k;
    __3CTX(&frame);
    func_001757D0(&group,contactCount,contacts,objectCount,objects);
    for(i=0;i<contactCount;i++){
        DZS *state;
        contact=contacts[i];
        row=&group.rows[i];
        state=&group.states[i];
        state->source=contact;
        state->normal=contact->normal;
        switch(contact->kind){
        case 11:
            row->kind=1;
            row->lower=-FLT_MAX;
            row->upper=FLT_MAX;
            break;
        case 14:
            if(flags&1){
                row->lower=contact->start*ClockDt();
                row->upper=contact->end*ClockDt();
                row->kind=contact->start<0.0f;
            }else{
                row->lower=0.0f;
                row->kind=0;
                row->upper=FLT_MAX;
            }
            break;
        default:
            row->kind=0;
            row->lower=0.0f;
            row->upper=FLT_MAX;
            break;
        }
        func_001758A0(&group,row,state);
    }
    if(flags&4){
        maximum=0.0f;
        for(i=0;i<contactCount;i++){
            float magnitude;
            contact=contacts[i];
            row=&group.rows[i];
            if(row->kind==1)row->target.value=contact->value;else row->target.value=contact->value+1.0f;
            magnitude=__builtin_fabsf(contact->value);
            if(maximum<magnitude)maximum=magnitude;
        }
        func_00175BD8(&group,4);
        func_00176070(&group,maximum+maximum,6.2831855f);
        {int j;for(j=0;j<objectCount;j++){}
        for(j=0;j<objectCount;j++)Callback(objects[j],71);}
        if(flags==4){func_00175870(&group,2);_$_3CTX(&frame,2);return;}
        func_0011B3F8(&group);
    }
    maximum=100.0f;
    fResting=flags&1;
    j=fResting;
    if(fResting){
        int n;
        RecalcSwXpPos(game,contactCount,contacts);
        RecalcSwXpMovement(game,contactCount,contacts);
        for(n=0;n<contactCount;n++){
            float magnitude;
            contact=contacts[n];
            row=&group.rows[n];
            DotQStore(contact->velocity.q,contact->normal.q,&row->target.value);
            magnitude=LengthSquared(contact->velocity.q);
            if(maximum<magnitude)maximum=magnitude;
        }
    }else{
        for(j=0;j<contactCount;j++){
            float r,d,magnitude;
            __asm__("": :"r"(j),"r"(j),"r"(j));
            contact=contacts[j];
            row=&group.rows[j];
            r=contact->elasticity*GRandInRange(0.9f,1.1f);
            d=Dot(contact->velocity.q,contact->normal.q);
            row->target.value=r*d+d;
            magnitude=LengthSquared(contact->velocity.q);
            if(maximum<magnitude)maximum=magnitude;
        }
    }
    func_00175D70(&group,flags);
    magnitude=Sqrt(maximum);
    func_00176070(&group,magnitude+magnitude,50.0f);
    for(k=0;k<objectCount;k++){}
    if(fResting){
        for(k=0;k<objectCount;k++)Callback(objects[k],69);
        for(k=0;k<objectCount;k++){
            P *p=objects[k];
            float l1;
            MOTION *motion;
            int moving;
            if(p->first->kind==2||p->second->kind==2)break;
            l1=LengthSquaredNM(p->first->velocity.q);
            motion=p->motion;
            moving=l1>25.0f || LengthSquared(p->second->velocity.q)>0.0025000002f || LengthSquared(motion->linear.q)>25.0f || LengthSquared(motion->angular.q)>0.0025000002f;
            if(moving)break;
        }
        if(k>=objectCount){
            __asm__("": :"r"(k),"r"(k),"r"(k));
            {int k4;for(k4=0;k4<objectCount;k4++)func_00243860(objects[k4]);}
            RecalcSwXpPos(&D_00475480,contactCount,contacts);
            RecalcSwXpMovement(&D_00475480,contactCount,contacts);
        }
    }else{
        {int k2;for(k2=0;k2<objectCount;k2++)Callback(objects[k2],70);}
    }
    func_00175870(&group,2);
    _$_3CTX(&frame,2);
}
