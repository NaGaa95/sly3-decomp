// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Set the owner body's orientation from `basis`: relative to the parent's inverse rotation when it has a parent, then
// orthonormalise, clear the w words, stamp and notify (virtual slot 20 and the refresh helpers). Based on Sly 2 func_001F42E0.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct LO { M3 matrix; U position; M3 rotation; char pad[0x30]; LO *parent; int stamp; };
struct VTE { short delta,pad; void (*fn)(void *); };
struct P { char pad[0xC]; VTE *vt; char pad10[0x3C]; LO *object; };
struct G { char pad[0x44F4]; int stamp; };
extern G D_00475480;
extern "C" M3 func_0011C6F8(const M3 *);
extern "C" void func_0011C798(M3 *);
extern "C" void func_0023DF78(P *);
extern "C" void func_0028F260(P *,LO *);
extern "C" void func_0023C8F8(P *);
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" void func_0023D338(P *p,const M3 *basis)
{
    LO *object=p->object;
    if(!object)return;
    {
        M3 m;
        if(object->parent)
            m=Mul(func_0011C6F8(&object->parent->rotation),*basis);
        else
            m=*basis;
        func_0011C798(&m);
        M3 *dest=&p->object->matrix;
        *dest=m;
        dest->r[0].i[3]=0;
        dest->r[1].i[3]=0;
        dest->r[2].i[3]=0;
        int stamp=++D_00475480.stamp;
        p->object->stamp=stamp;
        p->vt[20].fn((char *)p+p->vt[20].delta);
        func_0023DF78(p);
        func_0028F260(p,p->object);
        func_0023C8F8(p);
    }
}
