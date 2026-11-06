// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned char byte;
typedef unsigned long ulong;
typedef union { qword q; float f[4]; int n[4]; } U;
struct M4 { qword r[4]; };
struct Ring { float t,g,length; int pad; struct M4 m; };
struct Sample { qword pos; float fraction; char pad14[7]; byte alpha; int pad1c; };
struct RGBA { byte c[4]; };
struct Batch { int count; char pad4[8]; U *positions; byte *uv; struct RGBA *colors; int pad18; struct Sample *samples; };
struct N { void *record; int count; struct Batch *batches; struct N *next; };
struct S { char pad[0xCC]; struct N *nodes; char padD0[0x104-0xD0]; float g; char pad108[0x130-0x108]; float fade; char pad134[8]; int count; struct Ring *array; int index; char pad148[0x160-0x148]; void *follow; };
extern struct CLOCK { float t,dt; } g_clock;
void func_0023CC40(struct S *);
static inline qword Broadcast(float f) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline qword Transform(const struct M4 *m,qword p) {
    qword r;
    __asm__("vmulax.xyz ACC,%1,%2x\n\tvmadday.xyz ACC,%3,%2y\n\tvmaddaz.xyz ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w" : "=j"(r) : "j"(m->r[0]),"j"(p),"j"(m->r[1]),"j"(m->r[2]),"j"(m->r[3])); return r;
}
static inline qword Blend(qword a,qword b,qword beta,qword alpha) { qword r; __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=&j"(r) : "j"(a),"j"(beta),"j"(b),"j"(alpha)); return r; }
static inline float GetY(qword q) { float r; __asm__("prot3w %0,%1" : "=r"(r) : "r"(q)); return r; }
static inline float GetZ(qword q) { float r; __asm__("pextuw %0,$0,%1" : "=r"(r) : "r"(q)); return r; }
static inline float GetX(qword q) { float r; __asm__("mtc1 %1,%0" : "=f"(r) : "r"(q)); return r; }
static inline void StoreXYZ(U *dst,qword v) {
    qword q;
    float y,z;
    register float x asm("$f1"); /* pin: x lane in f1 */
    __asm__("qmfc2.ni %0,%1" : "=r"(q) : "j"(v));
    z=GetZ(q);
    y=GetY(q);
    x=GetX(q);
    dst->n[0]=(int)(x*16.0f);
    dst->n[1]=(int)(y*16.0f);
    dst->n[2]=(int)(z*16.0f);
}
void func_0026E9B0(struct S *p) {
    struct N *node;
    U scalar;
    float saved;
    for(node=p->nodes;node;node=node->next) {
        int i;
        for(i=0;i<node->count;i++) {
            struct Batch *batch=&node->batches[i];
            struct Sample *s=batch->samples;
            U *out=batch->positions;
            struct RGBA *color=batch->colors;
            byte *uv=batch->uv;
            int j;
            for(j=0;j<batch->count;j++,s++) {
                float t=s->fraction*(p->count-2);
                int k=(int)t;
                float alpha=t-k;
                int ia=(p->index+p->count-k-1)%p->count;
                int ib=(ia+p->count-1)%p->count;
                struct Ring *a=&p->array[ia],*b=&p->array[ib];
                qword va=s->pos,wa=Broadcast(alpha),wb=Broadcast(1.0f-alpha),pa,pb,pos;
                scalar.q=wb;
                pa=Transform(&a->m,va);
                scalar.q=wa;
                pb=Transform(&b->m,va);
                pos=Blend(pa,pb,wb,wa);
                StoreXYZ(out,pos);
                out++;
                if(color) {
                    float fade=1.0f-(g_clock.t-a->t)/p->fade;
                    float c;
                    if(fade<0.0f) c=0.0f;
                    else if(1.0f<fade) c=1.0f;
                    else c=fade;
                    color->c[3]=(int)(a->g*c*s->alpha);
                    color++;
                }
                if(uv && p->follow) {
                    ulong t=(int)(((1.0f-alpha)*a->length+alpha*b->length)*4096.0f);
                    ulong high=t>>8;
                    __asm__("sb %1,%0" : "=m"(uv[0]) : "r"(t));
                    __asm__("sb %1,%0" : "=m"(uv[1]) : "r"(high));
                    uv+=6;
                }
            }
        }
    }
    saved=p->g;
    p->g=1.0f;
    func_0023CC40(p);
    p->g=saved;
}
