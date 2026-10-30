// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/func_001604E8.cpp.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { qword r[3]; };
struct M4 { U r[4]; };
struct Source { char pad[0x40]; M4 m40; };
struct Dest { M4 m; char pad[0xA0-0x40]; Source *parent; int stamp; };
struct S { Source *source; Dest *dest; int position,rotation; };
struct G { char pad[0x44F4]; int counter; };
extern G D_00475480;
extern "C" M4 func_0011D768(const M4 *m);
extern "C" M3 func_0011C6F8(const M3 *m);
extern "C" void func_0011C798(M3 *m);
extern "C" qword *func_002BA818(qword *p,qword v);
static inline qword Transform(const M4 &m,qword p) {
 qword r;
 __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
 :"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(p));return r;
}
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
 qword a0=a.r[0],a1=a.r[1],a2=a.r[2];
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2]));
}
extern "C" void func_00182928(void *,S *s)
{
 M3 m;
 if(s->position) {
  M4 inv=func_0011D768(&s->dest->parent->m40);
  Dest *dest=s->dest;
  func_002BA818(&dest->m.r[3].q,Transform(inv,s->source->m40.r[3].q));
  dest->m.r[3].f[3]=1.0f;
 }
 if(s->rotation) {
  m=Mul(func_0011C6F8((M3 *)&s->dest->parent->m40),*(M3 *)&s->source->m40);
  func_0011C798(&m);
  Dest *dest=s->dest;
  dest->m.r[0].q=m.r[0];
  dest->m.r[1].q=m.r[1];
  dest->m.r[2].q=m.r[2];
  dest->m.r[0].i[3]=0;
  dest->m.r[1].i[3]=0;
  dest->m.r[2].i[3]=0;
 }
 int stamp=++D_00475480.counter;
 s->dest->stamp=stamp;
}
