// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_001995D8.cpp (extent values now constants/rodata LMs).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3]; M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct M4 {U r[4];};
struct LM {float gMin,gMax;};
/* rodata at 0x003212B0 (not in symbol_addrs); placed by bytes */
static const LM s_lmA={-50.0f,75.0f};
static const LM s_lmB={-150.0f,75.0f};
extern qword D_00317550;
extern "C" M3 func_0011C8C0(qword,float);
static inline qword Pack(float x,float y,float z){U u;qword q,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));u.q=q;return q;}
static inline qword Rot(const M3&m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(v));return r;}
static inline qword Transform(const M4*m,qword v){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(v));return r;}
static inline void Set(U*v,float x,float z){v->f[0]=x;v->i[1]=0;v->f[2]=z;}
extern "C" void func_00176578(const M4*world,int count,U*out){
 M3 m;U *cursor=out,*v;
 Set(cursor++,50.0f,s_lmB.gMax);Set(cursor++,50.0f,s_lmB.gMin);Set(cursor++,-60.0f,s_lmA.gMax);v=cursor++;Set(v,50.0f,s_lmB.gMax);
 float x=-60.0f,y=v->f[1];qword a=Pack(x,y,s_lmA.gMax),b=Pack(x,y,s_lmA.gMin);
 int i;for(i=8;i>=0;i--){m=func_0011C8C0(D_00317550,(i-4)*0.261799395084381103515625f);U*v0=cursor++;U*v1=cursor++;v0->q=Rot(m,a);v1->q=Rot(m,b);}
 cursor=out;i=count;while(--i>=0){cursor->q=Transform(world,cursor->q);cursor++;}
}
