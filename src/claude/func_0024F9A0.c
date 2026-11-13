// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 HitStepSupport (sly2-decomp src/hand/func_00205670.c), -Os; the triangle
// fetch goes through an inline taking three vertex pointers.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int i[4];} V;
struct P {char pad[0x218];int enabled;};
extern qword D_00317550;
void func_0024FB00(struct P*,V(*)[3]);
int func_001207A8(qword,qword,qword,qword,qword,float*,float*);
static inline qword Sub(const qword*a,const qword*b){qword av=*a,bv=*b;register qword r __asm__("vf3"); /* pin: result in vf3 */__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(av),"j"(bv));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,float f,V *k){qword q,r;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));k->q=q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k->q));return r;}
static inline float Normal(V*v,const qword*fallback){qword a=v->q;qword d;qword one;float g,r;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(one):"j"(d));
__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(one));
if(g<0.0001f)v->q=*fallback;
else {qword normalized;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=&j"(normalized):"j"(a),"j"(one));v->q=normalized;}
__asm__("mtc1 %1,%0":"=f"(r):"r"(one));return r;}
static inline int Hit(qword d,qword f,V*a,V*b,V*c,float*dist){return func_001207A8(d,f,a->q,b->q,c->q,dist,0);}
int func_0024F9A0(struct P*p,qword from,qword to,qword*out)
{
    V tri[2][3],d,k;
    float distance,length;
    unsigned i;
    if(!p->enabled)return 0;
    func_0024FB00(p,tri);
    d.q=Sub(&to,&from);
    length=Normal(&d,&D_00317550);
    for(i=0;i<2;i++){
        int hit=Hit(d.q,from,&tri[i][0],&tri[i][1],&tri[i][2],&distance);
        if(distance<=length && (hit&1)){
            *out=Add(from,Scale(d.q,distance,&k));
            return 1;
        }
    }
    return 0;
}
