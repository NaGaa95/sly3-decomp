// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002314D8: bakes per-vertex path samples (hit offset in the path frame + distance) for every mesh entry.
// func_0011CBF0 (look-at basis) is declared void here: its returned pointer is unused, so the call does not set $v0.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { U a, b, c; };
struct M4 { qword a, b, c, d; };
struct IV { int x, y, z, w; };
struct VTE { short d; short p; void *fn; };
struct E { int n; char pad4[8]; IV *vertices; char pad10[0x1C - 0x10]; U *samples; };
struct OWNER { char pad[0x40]; M4 mat; };
struct STATE { int pad; OWNER *object; char pad8[0x28 - 8]; };
struct MESH { char pad[0x14]; };
struct NODE { MESH *mesh; int n; E *entries; NODE *next; };
struct CONFIG { char pad[0x3C]; MESH *meshes; STATE *states; };
struct S { char pad0[0xC]; VTE *vt; char pad10[0x70 - 0x10]; char config[0xAC - 0x70]; MESH *meshes; STATE *states; char padB4[0xCC - 0xB4]; NODE *head; char padD0[0x130 - 0xD0]; void *path; };
struct AL { int cb, align; };
union PHASE { AL request; U hit; U vertex; };
extern char D_0034A160[];
extern "C" {
void func_0023C580(S *);
void func_00194F60(void *, int);
void func_001D2898(void *, const void *, unsigned);
void *func_001D2470(AL *);
void func_0022EA88(void *, qword, void *, qword *, qword *, float *, float *);
void func_0011CBF0(M3 *, qword, qword);
void func_002314D8(S *);
}
static inline qword Point(M4 *m, qword v)
{
    qword r = m->a;
    __asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w"
            : "+j"(r) : "j"(m->b), "j"(m->c), "j"(m->d), "j"(v));
    return r;
}
static inline qword Transform(const M3 &m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
            : "+j"(v) : "j"(m.a.q), "j"(m.b.q), "j"(m.c.q));
    return v;
}
static inline qword PointDifference(qword world, qword hit)
{
    qword value = world;
    __asm__("vsub.xyzw %0,%0,%1" : "+j"(value) : "j"(hit));
    return value;
}
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
// MMI 3x3 transpose (engine inline)
static inline void TransposeInto(M3 &r, const M3 &m)
{
    qword lo, hi, lo1, hi1;
    qword a, b, d;
    __asm__("pextlw %0,%5,%4\n\tpextuw %1,%5,%4\n\tpextlw %2,$zero,%6\n\tpextuw %3,$zero,%6"
            : "=&r"(lo), "=&r"(hi), "=&r"(lo1), "=&r"(hi1) : "r"(m.a.q), "r"(m.b.q), "r"(m.c.q));
    __asm__("pcpyld %0,%4,%3\n\tpcpyud %1,%3,%4\n\tpcpyld %2,%6,%5"
            : "=&r"(a), "=&r"(b), "=r"(d) : "r"(lo), "r"(lo1), "r"(hi), "r"(hi1));
    r.a.q = a; r.b.q = b; r.c.q = d;
}
void func_002314D8(S *p)
{
    IV vertices[128];
    PHASE phase;
    U direction;
    M3 basis, temporary, inverse;
    float distance;
    func_0023C580(p);
    if (!p->path || !p->head) return;
    qword axis = ((M3 *(*)(void *))p->vt[36].fn)((char *)p + p->vt[36].d)->c.q;
    for (NODE *node = p->head; node; node = node->next) {
        int index = node->mesh - p->meshes;
        STATE *state = &p->states[index];
        OWNER *object = state->object;
        state->object = (OWNER *)D_0034A160;
        int j = 0;
        func_00194F60(p->config, index);
        if (j < node->n) {
            do {
                E *e = &node->entries[j];
                int k = 0;
                func_001D2898(vertices, e->vertices, e->n * 16);
                PHASE *pp = &phase;
                phase.request.cb = e->n * 16;
                pp->request.align = 16;
                U *out = (U *)func_001D2470(&pp->request);
                e->samples = out;
                for (k = 0; k < e->n; k++) {
                    qword v = Make((float)vertices[k].x * 0.0625f, (float)vertices[k].y * 0.0625f, (float)vertices[k].z * 0.0625f);
                    qword world = Point(&object->mat, v);
                    phase.vertex.q = v;
                    func_0022EA88(p->path, world, 0, &pp->hit.q, &direction.q, &distance, 0);
                    func_0011CBF0(&temporary, direction.q, axis);
                    qword difference = PointDifference(world, phase.hit.q);
                    basis = temporary;
                    TransposeInto(temporary, basis);
                    inverse = temporary;
                    out->q = Transform(inverse, difference);
                    out->f[3] = distance;
                    out++;
                }
                j++;
            } while (j < node->n);
        }
    }
}
