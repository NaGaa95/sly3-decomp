// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
// Re-expresses the particles of an emitter batch when its space changes: the owner's (or attached object's) matrices and the
// optional second object's matrix are combined into a base matrix, the batch positions are carried through it and back through
// the inverse of the target space, and the velocities are rotated and corrected by the moving space.
// Matching notes: the struct-returning calls assign through compiler temporaries; the locals base/m/w/n are declared where the
// previous block's temporaries are free so the slots line up; `scratch`/`np` are pointer variables (their own registers);
// the lane stores through an int cast are direct frame accesses while the ones through `wv` use the pointer register.
typedef int qword __attribute__((mode(TI)));
struct Mat3 { qword rows[3]; };
struct Mat4 { Mat3 rot; qword position; };
union Vec { qword q; float f[4]; int bits[4]; };
struct VTE { short delta, pad; void *fn; };
struct VT { char pad[0x128]; VTE e128; };
struct XF { char pad[0x40]; Mat4 world; };
struct Object;
struct Source { char pad[0x60]; Object *frame; char pad64[0xDC - 0x64]; unsigned flags; };
struct Object { char pad0[0xC]; VT *vt; Source *src; char pad14[0x40 - 0x14]; Mat4 mat; };
struct Owner { char pad0[0x10]; Source *src; Object *a; Object *b; char pad1C[4]; Mat4 mat; Object *c; };
struct Settings { char pad[0x60]; int mode; int flag; };
struct Config { char pad[0x14]; Settings *settings; };
struct Emitter { Owner *owner; Config *config; };
struct Batch { int count; qword *pos; qword *vel; };
extern "C" {
Mat4 func_0011D558(const Mat4 *first, const Mat4 *second);
Mat4 func_0011D768(const Mat4 &in);
Mat4 func_0028BAD0(XF *xf, XF *relative);
Mat4 func_001C9708(Object *frame, Object *object, const Mat4 *m);
qword *func_002BA818(qword *out, qword v);
void *func_00292034(void *p, int v, int n);
}
static inline XF *WorldOf(Object *o, Mat4 *scratch)
{
    VTE *e = &o->vt->e128;
    return ((XF *(*)(void *, Mat4 *))e->fn)((char *)o + e->delta, scratch);
}
static inline qword Transform(const Mat4 &m, qword v)
{
    qword r;
    asm("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=j"(r) : "j"(m.rot.rows[0]), "j"(m.rot.rows[1]), "j"(m.rot.rows[2]), "j"(m.position), "j"(v));
    return r;
}
static inline qword Rotate(const Mat4 &m, qword v)
{
    qword r;
    asm("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r) : "j"(m.rot.rows[0]), "j"(m.rot.rows[1]), "j"(m.rot.rows[2]), "j"(v));
    return r;
}
// Rotate with the first row passed separately (the caller reads it from the variable, the other two through a pointer).
static inline qword Rotate(qword r0, const Mat3 *m, qword v)
{
    qword r;
    asm("vmulax.xyz $ACC,%2,%1x
	vmadday.xyz $ACC,%3,%1y
	vmaddz.xyz %0,%4,%1z"
        : "=j"(r) : "j"(v), "j"(r0), "j"(m->rows[1]), "j"(m->rows[2]));
    return r;
}
static inline qword Add(qword a, qword b) { qword r; asm("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; asm("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
extern "C" void func_00200328(Emitter *self, Batch *in)
{
    Owner *owner = self->owner;
    Object *a = owner->a;
    Object *b = owner->b;
    Object *c = owner->c;
    Settings *cfg = self->config->settings;
    Mat4 base, m;
    if (a && a == c && !cfg->mode && !b)
        return;
    if (a) {
        Mat4 *scratch = &m;
        XF *xf = WorldOf(a, scratch);
        base = func_0011D558(&xf->world, scratch);
        m = func_0028BAD0(xf, 0);
    } else {
        base = owner->mat;
        func_00292034(&m, 0, 0x40);
    }
    Mat4 w;
    if (b) {
        Object *frame = b->src->frame;
        const Mat3 *src = &b->mat.rot;
        Mat4 *wp = &w;
        func_002BA818(&wp->position, b->mat.position);
        wp->rot = *src;
        ((int *)&w)[11] = 0;
        ((int *)&w)[7] = 0;
        ((int *)&w)[3] = 0;
        ((Vec *)wp)[3].f[3] = 1.0f;
        w = func_001C9708(frame, a, &w);
        base = func_0011D558(&base, &w);
        m = func_0011D558(&m, &w);
    }
    Mat4 n;
    if (c) {
        Mat4 *np = &n;
        XF *xf = WorldOf(c, np);
        w = func_0011D558(&xf->world, np);
        if (!cfg->flag)
            n = func_0028BAD0(xf, 0);
        else
            func_00292034(np, 0, 0x40);
        unsigned flags = self->owner->src->flags;
        if (flags) {
            if (flags & 1) {
                Vec *wv = (Vec *)&w;
                func_00292034(wv, 0, 0x30);
                wv[2].f[2] = 1.0f;
                wv[1].f[1] = 1.0f;
                wv[0].f[0] = 1.0f;
                func_00292034(np, 0, 0x30);
            }
            if (flags & 2) {
                ((int *)&w)[12] = 0;
                ((int *)&n)[12] = 0;
            }
            if (flags & 4) {
                ((int *)&w)[13] = 0;
                ((int *)&n)[13] = 0;
            }
            if (flags & 8) {
                ((int *)&w)[14] = 0;
                ((int *)&n)[14] = 0;
            }
        }
    } else {
        func_00292034(&w, 0, 0x40);
        Vec *wv = (Vec *)&w;
        wv[3].f[3] = 1.0f;
        wv[2].f[2] = 1.0f;
        wv[1].f[1] = 1.0f;
        wv[0].f[0] = 1.0f;
        func_00292034(&n, 0, 0x40);
    }
    Mat4 inv = func_0011D768(w);
    Mat4 *invp = &inv;
    for (int k = 0; k < in->count; k++) {
        qword p = Transform(base, in->pos[k]);
        qword vel;
        switch (cfg->mode) {
        case 0:
            vel = Add(Rotate(base, in->vel[k]), Transform(m, p));
            break;
        case 1:
            vel = Rotate(base, in->vel[k]);
            break;
        case 2:
            vel = in->vel[k];
            break;
        }
        in->pos[k] = Transform(inv, p);
        in->vel[k] = Rotate(inv.rot.rows[0], &invp->rot, Sub(vel, Transform(n, p)));
    }
}
