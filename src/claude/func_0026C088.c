// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 SO update: release finished anims, state switch (jump table 0x328B00), queue an anim on a sideways move.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void (*method)(void *, qword); };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct SO {
    char pad[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; void *p134; char pad138[0x190 - 0x138]; int n190; float f194;
    char pad198[0x1BC - 0x198]; int n1BC; qword q1C0; char pad1D0[0x1E0 - 0x1D0]; float f1E0;
    char pad1E4[0x280 - 0x1E4]; void *p280; void *p284; char pad288[0x2B4 - 0x288]; void *p2B4; void *p2B8; void *p2BC; void *p2C0;
};
extern struct CLOCK { float t; } g_clock;
extern const struct VECTOR4 D_00328B80, D_00328B90;
void func_0023C660(struct SO *);
int func_00138AC8(void *);
void func_00137688(void **);
int func_001A7A80(void *, int, float);
void *func_002459F8(int);
void func_00244F08(void *, int);
void *func_001F4A80(struct SO *);
void func_00168670(void *, int);
void func_0026D470(struct SO *);
void func_0026DAB8(struct SO *);
void func_0026D9F0(struct SO *);
void func_0026D7B0(struct SO *, int);
void func_0026D340(struct SO *);
void func_0026D450(struct SO *);
void func_0026D1E8(struct SO *, const struct VECTOR4 *);
void func_0026CD30(struct SO *, int);
int func_00260758(void *, int);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
#define VCALLQ(po, n, q) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta, q))
void func_0026C088(struct SO *p)
{
    void *plo;
    func_0023C660(p);
    if (p->p2BC && func_00138AC8(p->p2BC)) func_00137688(&p->p2BC);
    if (p->p2B8 && func_00138AC8(p->p2B8)) func_00137688(&p->p2B8);
    if (p->p2B4 && func_00138AC8(p->p2B4)) func_00137688(&p->p2B4);
    if (p->n190 != 0 && p->n190 != 5 && func_001A7A80(p->p134, 0x200, 0.0f)) {
        func_00244F08(func_002459F8(0x2A), 0);
        func_00168670(func_001F4A80(p), 0);
    }
    plo = 0;
    switch (p->n190) {
    case 1:
        func_0026D470(p);
        func_0026DAB8(p);
        func_0026D9F0(p);
        func_0026D7B0(p, 0);
        if (p->n1BC) func_0026D340(p);
        break;
    case 2:
        if (func_001A7A80(p->p134, 0x10, 0.0f) && p->f1E0 < 0.0f) {
            func_0026D450(p);
            func_0026D1E8(p, &D_00328B80);
            plo = p->p280;
        } else if (func_001A7A80(p->p134, 0x40, 0.0f) && 0.0f < p->f1E0) {
            func_0026D450(p);
            func_0026D1E8(p, &D_00328B90);
            plo = p->p284;
        }
        func_0026DAB8(p);
        func_0026D9F0(p);
        func_0026D7B0(p, 0);
        break;
    case 3:
        if (g_clock.t - p->f194 > 0.5f) {
            VCALLQ(p, 34, p->q1C0);
            func_0026CD30(p, 4);
        }
        break;
    case 4:
        func_0026D470(p);
        func_0026DAB8(p);
        func_0026D9F0(p);
        func_0026D7B0(p, 0);
        if (!func_00260758(p->p2C0, 0x3F1)) func_0026CD30(p, 1);
        break;
    case 5:
        func_0026D9F0(p);
        func_0026D7B0(p, 0);
        break;
    }
    if (plo && !p->p2B4) func_00137588(plo, p, 1, &p->p2B4, 0.0f, 1.0f);
}
/* the rest of this unit's .rodata block after the jump table (0x328B18..0x328B2F):
   D_00328B18 is used by func_0026C420, the -FLT_MAX literal at 0x328B24 by func_0026C990 */
struct SMP { float a, b, c; };
extern const struct SMP D_00328B18 __attribute__((aligned(8))) = { 1.0f, 0.0f, 0.2f };
extern const float D_00328B24 = -3.40282346638528859812e+38f;
