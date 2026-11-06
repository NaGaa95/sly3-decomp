// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Apply queued translation and rotation, then refresh changed objects.
typedef int qword __attribute__((mode(TI)));
union U {qword q;int i[4];float f[4];};
struct M3 {qword r[3];};
struct LO {M3 matrix;U position;char pad40[0x60];LO *parent;int stamp;};
struct VE {short delta,pad;void(*fn)(void*);};
struct P {char padC[0xC];VE *vt;char pad10[0x38];LO *translation,*rotation;char pad50[0x88];int enabled;char padEC[4];U shift,turn;};
extern qword D_00317560;
extern struct GAME {char pad[0x44F4];int stamp;} D_00475480;
extern "C" int func_0011E9F0(float,float,float);
extern "C" void func_0028F260(P *,LO *);
extern "C" qword func_0028E990(void *,LO *,qword);
extern "C" qword *func_002BA818(qword *,qword);
extern "C" M3 func_0011C930(qword);
extern "C" void func_0023DD40(P *);
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline void Near(int*out,qword a,qword b){if(func_0011E9F0(X(a),X(b),0.0001f))if(func_0011E9F0(Y(a),Y(b),0.0001f))*out=func_0011E9F0(Z(a),Z(b),0.0001f)!=0;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%1,%0":"+j"(b):"j"(a));return b;}
static inline M3 Mul(const M3&a,const M3&b) return r {
    qword a0=a.r[0],a1=a.r[1],a2=a.r[2];
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2]));
}
static inline qword Consume(P*p,LO*object,U&pending){func_0028F260(p,object);qword world=func_0028E990(0,object->parent,pending.q);pending.i[2]=0;pending.i[1]=0;return world;}
extern "C" void func_00244138(P*p)
{
    M3 final;
    int changed=0;
    if(p->enabled){
        int near=0;
        Near(&near,D_00317560,p->shift.q);
        if(!near){
            LO *object=p->translation;
            changed=1;
            qword shift=Consume(p,object,p->shift);
            p->shift.i[0]=0;
            func_002BA818(&object->position.q,Add(object->position.q,shift));
            object->position.f[3]=1.0f;
            object->stamp=++D_00475480.stamp;
        }
        near=0;Near(&near,D_00317560,p->turn.q);
        if(!near){
            LO *object=p->rotation;
            changed=1;
            qword turn=Consume(p,object,p->turn);
            p->turn.i[0]=0;
            final=Mul(func_0011C930(turn),object->matrix);
            object->matrix=final;
            ((int*)&object->matrix.r[1])[3]=0;
            ((int*)&object->matrix.r[2])[3]=0;
            ((int*)&object->matrix.r[0])[3]=0;
            object->stamp=++D_00475480.stamp;
        }
        if(changed){p->vt[20].fn((char*)p+p->vt[20].delta);func_0023DD40(p);}
    }
}
