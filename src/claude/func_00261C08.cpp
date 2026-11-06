// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_00213300.cpp; target Sly 3 0x00261C08.
// Flush the sprite render queue and pair begin/end VU microprogram packets.
typedef unsigned int uint;
typedef unsigned char uchar;
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
struct PARAM {
    int mode, pad4; float priority; int padC; V4 offset, scale;
    PARAM(float p) { offset.x = 0.0f; offset.y = 0.0f; offset.z = 0.0f; offset.w = 0.0f; scale.x = 0.0f; scale.y = 0.0f; scale.z = 0.0f; scale.w = 0.0f; priority = p; mode = 1; }
    PARAM() {}
};
struct Q { uchar color0[4], color1[4]; char pad8[8]; char matrix[0x20]; void *payload; int kind; char pad38[0x30]; Q *next; };
struct LIST { Q *first, *last; };
struct S { char pad[0x74]; void *sprites; char pad78[0x1C]; int count; char pad98[0x5C]; LIST queue; char padFC[4]; char name[1]; };
struct R { unsigned char *base; int pad[2]; unsigned char *cur; };
extern R D_0036C308;
extern const char D_00327F28[];
extern "C" {
void func_001C8238(S *);
int func_00261BD0(S *);
void func_002677F0(void *);
void func_002618C8(int, void *, const char *, const char *, float);
void func_00266478(S *, int, float);
void func_00264818(void *, void *, PARAM *);
void func_0011AD70(LIST *);
}
static inline void Align(R *r) { while ((uint)r->cur & 63) { *(uint *)r->cur = 0; r->cur += 4; } }
static inline float Min(float x, float y) { return y < x ? y : x; }
static inline float Max(float x, float y) { return x < y ? y : x; }
static inline void Offset(V4 &v, float x, float y, float z, float w) { v.x = (x - 127.0f) * 2.0f; v.y = (y - 127.0f) * 2.0f; v.z = (z - 127.0f) * 2.0f; v.w = (w - 127.0f) * 2.0f; }
static inline void SetOffset(V4 &v, const uchar *c) { Offset(v, c[0], c[1], c[2], c[3]); }
static inline float ColorScale(int c, float upper) { return Max(Min((c - 127) * 0.007874016f, upper), -1.0f); }
static inline void Scale(V4 &v, int a, int b, int d, int e, float upper) { float x = ColorScale(a, upper), y = ColorScale(b, upper), z = ColorScale(d, upper), w = ColorScale(e, upper); v.x = x; v.y = y; v.z = z; v.w = w; }
static inline void SetScale(V4 &v, const Q *q, float upper) { Scale(v, q->color1[0], q->color1[1], q->color1[2], q->color1[3], upper); }
static inline Q *Begin(S *p, R *r) { Align(r); uint c = (uint)r->cur, b = (uint)r->base; c |= 0x30000000; b |= 0x30000000; r->cur = (unsigned char *)c; r->base = (unsigned char *)b; Q *pending = 0; func_002618C8(2, p->name, D_00327F28, "zbuf clear", p->count); return pending; }
static inline void Finish(R *r, S *p) { Align(r); uint c = (uint)r->cur, b = (uint)r->base; c &= 0x0FFFFFFF; b &= 0x0FFFFFFF; r->cur = (unsigned char *)c; r->base = (unsigned char *)b; Q *q = p->queue.first; while (q) { Q *old = q; q = q->next; old->next = 0; } func_0011AD70(&p->queue); }
extern "C" void func_00261C08(S *p)
{
    func_001C8238(p);
    if (!func_00261BD0(p))
        return;
    func_002677F0(p->sprites);
    float priority = 16.0f;
    Q *pending = Begin(p, &D_0036C308);
    Q *q = p->queue.first;
    while (q) {
        if (q->kind == 1) {
            PARAM param(priority);
            func_00266478(p, 1, priority - 1.0f);
            pending = q;
            func_00264818(q->payload, q->matrix, &param);
            func_00266478(p, 3, param.priority + 1.0f);
        } else if (q->kind == 4) {
            if (pending) {
                float one = 1.0f;
                PARAM param(priority);
                func_00266478(p, 2, priority - one);
                func_00264818(pending->payload, pending->matrix, &param);
                pending = 0;
                func_00266478(p, 4, param.priority + one);
            }
            if (q->payload) {
                PARAM second;
                SetOffset(second.offset, q->color0);
                SetScale(second.scale, q, 1.0f);
                second.priority = priority += 256.0f;
                second.mode = 1;
                func_00264818(q->payload, q->matrix, &second);
            }
        } else if (q->payload) {
            PARAM param;
            SetOffset(param.offset, q->color0);
            SetScale(param.scale, q, 1.0f);
            param.priority = priority;
            param.mode = 1;
            func_00264818(q->payload, q->matrix, &param);
        }
        q = q->next;
        priority += 256.0f;
    }
    Finish(&D_0036C308, p);
}
