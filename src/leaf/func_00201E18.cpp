// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
// Wraps the particles of an emitter around its box: for a box-shaped volume (type 1) every live particle is moved into the
// volume's local space; a coordinate outside [min, max] is shifted by the box size, and a moved particle is transformed back.
#include "../P2/mat.h"
union U { qword q; float f[4]; };
struct KindInfo { unsigned char pad0[0xD8]; int kind; };
struct Shape;
struct Source { KindInfo *info; unsigned char pad4[0xC]; Shape *shape; };
struct Shape { U min; U max; unsigned char pad20[0x48 - 0x20]; int type; };
struct Frame { qword pos[43]; qword vel[43]; qword data[43]; qword pad[3]; };
struct Block {
    Frame frames[2];
    int frame;
    int count;
    int pad1088, pad108C;
    Block *next;
};
struct VTE { short delta, pad; void *fn; };
struct Target { unsigned char pad0[0xC]; VTE *vt; };
struct Owner { unsigned char pad0[0x14]; Target *target; };
struct Emitter { Owner *owner; Source *source; unsigned char pad8[0x50 - 8]; Block *first; };
extern "C" {
MATRIX4 func_0011D558(const MATRIX4 *first, const MATRIX4 *second);
MATRIX4 func_0011D768(const MATRIX4 &in);
void func_002BC3D8(void *self, int flags);
}
struct Guard { ~Guard() { func_002BC3D8(this, 2); } };
static inline qword TransformPoint(const MATRIX4 *matrix, qword point)
{
    const qword *columns = (const qword *)matrix;
    qword result;
    asm("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=j"(result) : "j"(columns[0]), "j"(columns[1]), "j"(columns[2]), "j"(columns[3]), "j"(point));
    return result;
}
extern "C" void func_00201E18(Emitter *emitter)
{
    if (emitter->source->info->kind != 3)
        return;
    Shape *shape = emitter->source->shape;
    if (shape->type != 1)
        return;
    U bmin, bmax;
    bmin.q = shape->min.q;
    bmax.q = shape->max.q;
    float size[3];
    size[0] = bmax.f[0] - bmin.f[0];
    size[1] = bmax.f[1] - bmin.f[1];
    size[2] = bmax.f[2] - bmin.f[2];
    MATRIX4 toWorld, toLocal, scratch;
    Target *target = emitter->owner->target;
    VTE *e = &target->vt[37];
    MATRIX4 *base = (MATRIX4 *)(((char *(*)(void *, MATRIX4 *))e->fn)((char *)target + e->delta, &scratch) + 0x40);
    toWorld = func_0011D558(base, &scratch);
    toLocal = func_0011D768(toWorld);
    Guard guard;
    for (Block *block = emitter->first; block; block = block->next) {
        Frame *frame = &block->frames[block->frame];
        for (int i = 0; i < block->count; i++) {
            qword *pos = &frame->pos[i];
            int moved = 0;
            U local;
            local.q = TransformPoint(&toLocal, *pos);
            if (local.f[0] < bmin.f[0]) {
                local.f[0] += size[0];
                moved = 1;
            } else if (bmax.f[0] < local.f[0]) {
                local.f[0] -= size[0];
                moved = 1;
            }
            if (local.f[1] < bmin.f[1]) {
                local.f[1] += size[1];
                moved = 1;
            } else if (bmax.f[1] < local.f[1]) {
                local.f[1] -= size[1];
                moved = 1;
            }
            if (local.f[2] < bmin.f[2]) {
                local.f[2] += size[2];
                moved = 1;
            } else if (bmax.f[2] < local.f[2]) {
                local.f[2] -= size[2];
                moved = 1;
            }
            if (moved) {
                local.q = TransformPoint(&toWorld, local.q);
                float *out = (float *)pos;
                out[0] = local.f[0];
                out[1] = local.f[1];
                out[2] = local.f[2];
            }
        }
    }
}
