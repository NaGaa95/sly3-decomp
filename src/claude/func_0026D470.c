// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 SO input handling: direction vcalls on the input interface (vptr +0x2C, slot 1), aim offset update, buttons.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; unsigned int (*method)(void *, float, unsigned int); };
struct INPUT { char pad[8]; float f8; char padC[0x18 - 0xC]; unsigned int held18; char pad1C[0x2C - 0x1C]; struct VTE *vt; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct V3 { float x, y, z, w; };
struct SO {
    char pad[0x134]; struct INPUT *p134; char pad138[0x198 - 0x138]; int n198;
    char pad19C[0x21C - 0x19C]; float f21C; char pad220[0x228 - 0x220]; int n228; char pad22C[0x250 - 0x22C];
    qword q250; union { qword q; struct V3 v; } u260; char pad270[0x280 - 0x270];
    void *p280; void *p284; void *p288; void *p28C; void *p290; void *p294; char pad298[0x2B4 - 0x298]; void *p2B4;
};
extern struct CLOCK { float t, dt; } g_clock;
extern const struct VECTOR4 D_00328B80, D_00328B90, D_00328BA0, D_00328BB0, D_00328BC0, D_00328BD0;
extern const float D_00328B48[2];
void func_0026D1E8(struct SO *, const struct VECTOR4 *);
unsigned int func_001A7A80(void *input, unsigned int mask, float threshold);
void func_001A7B38(struct INPUT *, int, float *, float *);
float func_0011EE68(const void *limits, float value);
void func_0026D078(struct SO *);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
static inline void SetYZ(struct V3 *pv, float y, float z) { pv->y = y; pv->z = z; }
#define Query(pi, mask, g) ((pi)->vt[1].method((char *)(pi) + (pi)->vt[1].delta, g, mask))
void func_0026D470(struct SO *p)
{
    void *plo = 0;
    switch (p->n198) {
    case 0:
        if (Query(p->p134, 0x10, 0.0f)) {
            func_0026D1E8(p, &D_00328B80);
            plo = p->p280;
        } else if (Query(p->p134, 0x40, 0.0f)) {
            func_0026D1E8(p, &D_00328B90);
            plo = p->p284;
        }
        break;
    case 1:
    case 2:
        if (Query(p->p134, 0x10, 0.0f)) {
            func_0026D1E8(p, &D_00328BC0);
            plo = p->p290;
        } else if (Query(p->p134, 0x40, 0.0f)) {
            func_0026D1E8(p, &D_00328BD0);
            plo = p->p294;
        }
        if (0.2f <= p->p134->f8) {
            float a = p->u260.v.x, b = p->u260.v.y;
            float dx, dy;
            func_001A7B38(p->p134, 6, &dx, &dy);
            a = func_0011EE68(D_00328B48, a + dx * -2.0f * g_clock.dt);
            b = func_0011EE68(D_00328B48, b + dy * -2.0f * g_clock.dt);
            p->u260.v.x = a;
            SetYZ(&p->u260.v, b, 4000.0f);
        } else
            p->u260.q = p->q250;
        break;
    }
    if (Query(p->p134, 0x20, 0.0f)) {
        func_0026D1E8(p, &D_00328BB0);
        plo = p->p28C;
    } else if (Query(p->p134, 0x80, 0.0f)) {
        func_0026D1E8(p, &D_00328BA0);
        plo = p->p288;
    }
    if (func_001A7A80(p->p134, 8, 0.0f)) func_0026D078(p);
    if (func_001A7A80(p->p134, 0xF0, 0.0f)) {
        p->n228 = 0;
        if ((p->p134->held18 & 4) && 25.0f <= p->f21C) {
            p->n228 = 1;
            p->f21C -= 25.0f;
        }
    }
    if (plo && !p->p2B4) func_00137588(plo, p, 1, &p->p2B4, 0.0f, 1.0f);
}
