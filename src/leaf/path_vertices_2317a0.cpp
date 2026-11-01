// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Rebuild the fixed-point vertex arrays of a sampled path (Sly 2 func_001E9AC0 with 16.0f scaling): for every sample of every
// element, query the path at min(end, sample.w), build a frame from the path direction and the owner's up axis, transform the sample
// position by it, add the path position and store x/y/z * 16 as integers (16-byte stride).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword a, b, c; };
union U { qword q; float f[4]; };
struct E { int n; char pad4[8]; int *out; char pad10[0x1C - 0x10]; U *samples; };
struct NODE { int pad; int n; E *entries; NODE *next; };
struct VTE { short d; short p; void *fn; };
struct S { char pad0C[0xC]; VTE *vt; char pad10[0xCC - 0x10]; NODE *head; char padD0[0x130 - 0xD0]; void *path; };
extern "C" {
void func_0023CC40(S *);
float func_0022DFC0(void *);
void func_0022E148(void *, float, qword *, qword *);
M3 func_0011CBF0(qword, qword);
void func_002317A0(S *);
}
static inline qword Transform(M3 *m, qword a) { __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(a) : "j"(m->a), "j"(m->b), "j"(m->c)); return a; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GetX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float Min(float a, float b) { return b < a ? b : a; }
void func_002317A0(S *p)
{
    func_0023CC40(p);
    float end = func_0022DFC0(p->path);
    qword axis = ((M3 *(*)(void *))p->vt[36].fn)((char *)p + p->vt[36].d)->c;
    NODE *node;
    for (node = p->head; node; node = node->next) {
        int j;
        for (j = 0; j < node->n; j++) {
            E *e = &node->entries[j];
            U *src = e->samples;
            int *out = e->out;
            int k;
            for (k = 0; k < e->n; k++) {
                U pos, dir;
                func_0022E148(p->path, Min(end, src->f[3]), &pos.q, &dir.q);
                M3 m;
                M3 tmp = func_0011CBF0(dir.q, axis);
                m = tmp;
                qword result = Add(Transform(&m, src->q), pos.q);
                src++;
                out[0] = (int)(GetX(result) * 16.0f);
                out[1] = (int)(GetY(result) * 16.0f);
                out[2] = (int)(GetZ(result) * 16.0f);
                out += 4;
            }
        }
    }
    func_0023CC40(p);
}
