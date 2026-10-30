// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_001801B8).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {
 U r[3];
 M3(){}
 M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}
 M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}
};
struct VTE {short delta,pad;void*fn;};
struct P {char pad[0xC];VTE*vt;char pad10[0x194-0x10];int flag;char pad198[0x1F0-0x198];float time;char pad1F4[0xC];P*target;float turnRate;};
struct CLOCK{float time,dt;};
extern "C" CLOCK g_clock;
extern "C" qword D_00317550;
extern "C" void func_0023C660(P*);
static inline qword Position(P*p){VTE*e=&p->vt[36];return *(qword*)(((unsigned char*(*)(void*))e->fn)((char*)p+e->delta)+0x30);}
extern "C" float func_001205C8(qword);
extern "C" float func_0011E3B8(float);
extern "C" float func_0011E560(float,float);
extern "C" M3 func_0011C8C0(qword,float);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Transform(const M3&m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;}
static inline M3 Mul(const M3&a,const M3&b) return r
{
 qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" void func_0019CA58(P*p){
 func_0023C660(p);
 if(!p->flag&&p->time<=g_clock.time)((void(*)(void*,P*))p->vt[92].fn)((char*)p+p->vt[92].delta,0);
 if(!p->target||p->turnRate==0.0f)return;
 M3 rotation,matrix;
 qword position;
 position=Position(p->target);
 qword displacement=Sub(position,Position(p));
 float desired=func_001205C8(displacement);
 qword direction=((qword(*)(void*))p->vt[38].fn)((char*)p+p->vt[38].delta);
 float current=func_001205C8(direction);
 float angle=func_0011E560(func_0011E3B8(desired-current),p->turnRate*g_clock.dt);
 rotation=func_0011C8C0(D_00317550,angle);
 ((void(*)(void*,qword))p->vt[40].fn)((char*)p+p->vt[40].delta,Transform(rotation,direction));
 // The original reads this local matrix before initialization.
 matrix=Mul(rotation,matrix);
 ((void(*)(void*,M3*))p->vt[35].fn)((char*)p+p->vt[35].delta,&matrix);
}
