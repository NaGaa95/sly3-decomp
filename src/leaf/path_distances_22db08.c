// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Refresh the path: cache the transform (virtual slot 36), then rebuild the cumulative distance table (polyline length of the
// transformed points, or per-segment durations in the other mode) and notify the sub object. Based on Sly 2 func_001E6180.
typedef int qword __attribute__((mode(TI)));
struct M { qword a,b,c,d; };
struct VTE { short d,pad; void (*pf)(); };
struct S {
 char pad[0xC]; struct VTE *vt; char pad10[0xD0-0x10];
 int mode; char padD4[4]; int n; char padDC[4];
 float *dist; qword *v; char padE8[8]; struct M mat;
 char pad130[0x164-0x130]; float duration; int pad168; void *sub;
};
void func_0022DCB8(struct S*);
void func_0022D950(struct S*,int);
void func_002314A8(void*);
static inline qword Point(struct M *m,qword a) {
 qword r;
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));
 return r;
}
static inline qword Move(qword a) { qword r; __asm__("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r; }
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r; }
static inline qword LenVec(qword a) {
 qword d,one;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(a));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
 return d;
}
void func_0022DB08(struct S *p)
{
 int i;
 func_0022DCB8(p);
 p->mat=*((struct M*(*)(void*))p->vt[36].pf)((char*)p+p->vt[36].d);
 if (p->mode==0) {
  float *d0=p->dist; float total=0.0f;
  qword prev;
  prev=Point(&p->mat,p->v[0]);
  d0[0]=total;
  for(i=1;i<p->n;i++) {
   qword cur=Point(&p->mat,p->v[i]);
   qword lenv=LenVec(Sub(prev,cur));
   float len;
   prev=Move(cur);
   __asm__("mtc1 %1,%0":"=f"(len):"r"(lenv));
   total+=len;
   p->dist[i]=total;
  }
 } else {
  int j;
  p->dist[0]=0;
  for(j=0;j<p->n-1;j++) {
   func_0022D950(p,j);
   p->dist[j+1]=p->dist[j]+p->duration;
  }
 }
 if(p->sub)func_002314A8(p->sub);
}
