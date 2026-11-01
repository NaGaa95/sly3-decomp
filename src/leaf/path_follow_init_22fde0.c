// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Path follower setup: remember the path, allocate the point/distance buffers, set the tuning constants, transform the
// path points by the path matrix (virtual slot 36) and start/end positions, then run func_002314A8. Based on Sly 2 func_001E81C0.
typedef int qword __attribute__((mode(TI)));
struct M4 {qword a,b,c,d;};
struct AL {int cb,align;};
struct VTE {short d,pad;struct M4 *(*pf)(void*);};
struct PATH {char pad[0xC];struct VTE *vt;char pad10[0xD8-0x10];int n;int padEC;float *dist;qword *v;};
struct S {int a,b;float g8;char padC[0x20-0xC];qword start,end;void *fn40,*fn44;struct PATH *path;int n4C;int pad50;qword *v54,*v58;float *dist;float g60;char pad64[8];float g6C,g70;char pad74[0x84-0x74];int n84;float g88;};
extern char D_0034A160[];
void *func_001D2538(struct AL*);
void func_002314A8(struct S*);
static inline qword Point(struct M4 *m,qword a) {qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));return r;}
struct S *func_0022FDE0(struct S *p,struct PATH *path) {
 struct AL size;struct M4 *m;int i;
 p->path=path;p->n4C=-1;
 size.cb=path->n*16;size.align=16;p->v54=func_001D2538(&size);
 size.cb=path->n*16;size.align=16;p->v58=func_001D2538(&size);
 size.cb=path->n*4;size.align=16;p->dist=func_001D2538(&size);
 p->g8=-1750.0f;p->g60=3.0f;p->g6C=500.0f;p->g70=5.0f;
 p->a=0;p->b=0;
 p->n84=p->path->n;p->g88=300.0f;
 m=p->path->vt[36].pf((char*)p->path+p->path->vt[36].d);
 for(i=0;i<p->path->n;i++)p->v54[i]=Point(m,p->path->v[i]);
 p->fn40=p->fn44=D_0034A160;
 if(p->path->n>0) {
  p->start=p->v54[0];p->end=p->v54[p->path->n-1];
 }
 func_002314A8(p);
 return p;
}
