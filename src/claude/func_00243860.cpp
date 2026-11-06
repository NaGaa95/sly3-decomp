// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3];M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct OWNER {M3 matrix;U position;char pad40[0x60];OWNER *parent;int stamp;char padA8[8];U velocity;};
struct NODE {char pad10[0x18];unsigned long flags;char pad20[0x50];NODE *next;};
struct E {char pad34[0x34];NODE *first;};
struct VT {short delta,pad;void (*fn)(void *);};
struct P {char padC[0xC];VT *vt;char pad10[0x38];OWNER *position,*rotation;char pad50[0x8C];E *e;};
struct G {char pad[0x44F4];int stamp;};
struct CLOCK {float time,dt;};
extern CLOCK g_clock;
extern G D_00475480;
extern "C" void func_0028F2E0(P *,OWNER *);
extern "C" qword *func_002BA818(qword *,qword);
extern "C" M3 *func_0011C930(M3 *,qword);
static inline M3 BuildRotation(qword vector) return matrix {func_0011C930(&matrix,vector);}
extern "C" void func_0011C798(M3 *);
extern "C" void func_0023C8F8(P *);
extern "C" void func_0023C840(NODE *);
extern "C" void func_0023DEA0(P *);
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return out->q;}
static inline qword AddScaled(qword p,qword v,qword k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=&j"(r):"j"(p),"j"(v),"j"(k));return r;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(r):"j"(v),"j"(k));return r;}
static inline void Clear(U *v){v->i[2]=0;v->i[1]=0;v->i[0]=0;}
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" void func_00243860(P *p)
{
    U scalar;
    M3 frame;
    OWNER *position=p->position,*rotation=p->rotation;
    U *positionVelocity=&position->velocity,*rotationVelocity=&rotation->velocity;
    float coefficient=-0.5f;
    CLOCK *clock;
    G *global;
    NODE *node;
    func_0028F2E0(p,position);
    func_0028F2E0(p,rotation);
    clock=&g_clock;
    {qword point=position->position.q;
    qword k=Scalar(clock->dt*coefficient,&scalar);
    func_002BA818(&position->position.q,AddScaled(point,position->velocity.q,k));}
    position->position.f[3]=1.0f;
    global=&D_00475480;
    position->stamp=++global->stamp;
    Clear(positionVelocity);
    frame=Mul(BuildRotation(Scale(rotation->velocity.q,Scalar(clock->dt*coefficient,&scalar))),rotation->matrix);
    func_0011C798(&frame);
    {M3 *dest=&rotation->matrix;*dest=frame;dest->r[1].i[3]=0;dest->r[2].i[3]=0;dest->r[0].i[3]=0;}
    rotation->stamp=++global->stamp;
    Clear(rotationVelocity);
    p->vt[20].fn((char*)p+p->vt[20].delta);
    func_0023C8F8(p);
    if(p->e){
        for(node=p->e->first;node;node=node->next){
            if(!(node->flags&(1UL<<19)))func_0023C840(node);
        }
    }
    func_0023DEA0(p);
}
