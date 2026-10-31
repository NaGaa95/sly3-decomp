// CPP
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Re-aim the owner's body (kind 6) at `position` (port of Sly 2 func_001F46D8): after the common prelude, express the
// target point relative to the body's own rotation and store the resulting velocity.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct LO { M3 matrix; U position; M3 rotation; char pad[0x24]; int kind; short state; char pad9A[6]; LO *parent; int stamp; char padA8[8]; U velocity; };
struct VTE { short delta,pad; qword (*fn)(void *); };
struct P { char pad[0xC]; VTE *vt; char pad10[0x3C]; LO *object; };
extern "C" M3 func_0011C6F8(const M3 *);
extern "C" void func_0011C798(M3 *);
extern "C" void func_00292034(void *,int,int);
extern "C" void func_0028F260(P *,LO *);
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" int func_0028EFD8(int);
extern "C" void func_0028F068(P *,LO *,int);
extern "C" qword func_0028E990(LO *,LO *,qword);
extern "C" void func_0023DD40(P *);
extern "C" void func_0023E228(P *);
extern "C" void func_00241F00(P *,long);

static inline qword Sub(qword a,const qword *pb)
{
    qword r;
    register qword b __asm__("vf2"); /* register pin: the loaded operand lives in vf2 */
    __asm__("lqc2 %1,%3
	vsub.xyzw %0,%2,%1" : "=j"(r),"=&j"(b) : "j"(a),"m"(*pb));
    return r;
}
static inline qword Transform(const M3 &m,qword v) { qword r;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;
}
static inline void Clear(U *v) { v->i[2]=0;v->i[1]=0;v->i[0]=0; }
extern "C" void func_0023D718(P *p,qword position)
{
    LO *object=p->object;
    if(!object || object->kind!=6)return;
    if(!func_0028EFD8(object->state))func_0028F068(p,object,1);
    const M3 *rotation=&object->rotation;
    Clear(&object->velocity);
    M3 normalized;
    qword origin=p->vt[39].fn((char *)p+p->vt[39].delta);
    normalized=*rotation;
    func_0011C798(&normalized);
    M3 relative=Mul(*rotation,func_0011C6F8(&normalized));
    object->velocity.q=func_0028E990(0,object->parent,Transform(relative,Sub(position,&origin)));
    func_0028F260(p,object);
    func_0023DD40(p);
    func_0023E228(p);
    func_00241F00(p,0);
}
