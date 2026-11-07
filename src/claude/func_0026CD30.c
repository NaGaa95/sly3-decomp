// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 SO SetState (jump table 0x328B30); defines the next unit rodata D_00328B48 used by func_0026D470.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *method; };
struct LO { char pad[0xC]; struct VTE *vt; };
struct SO {
    char pad[0xC]; struct VTE *vt; char pad10[0x48 - 0x10]; void *p48; void *p4C; char pad50[0x190 - 0x50]; int n190; float f194;
    char pad198[0x1D4 - 0x198]; void *p1D4; void *p1D8; char pad1DC[0x1E0 - 0x1DC]; float f1E0;
    char pad1E4[0x27C - 0x1E4]; void *p27C; char pad280[0x2A4 - 0x280]; void *p2A4; void *p2A8; char pad2AC[4]; void *p2B0;
    void *p2B4; void *p2B8; void *p2BC; struct LO *p2C0;
};
extern struct CLOCK { float t; } g_clock;
extern qword D_00317560;
extern char D_0036C700[];
void func_00262450(struct LO *, int);
void func_0026D7B0(struct SO *, int);
void func_00240DB0(struct SO *);
void *func_001F4A80(struct SO *);
void func_00167960(void *, float);
void func_00166A40(void *);
void func_00225EE8(void *, struct SO *);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
void func_00137628(void **);
void func_001854C8(void *, int, struct SO *);
void func_0028F068(struct SO *, void *, int);
void func_0023EBF8(struct SO *, int);
#define VCALL(po, n) (((void (*)(void *))(po)->vt[n].method)((char *)(po) + (po)->vt[n].delta))
#define VCALLQ(po, n, q) (((void (*)(void *, qword))(po)->vt[n].method)((char *)(po) + (po)->vt[n].delta, q))
void func_0026CD30(struct SO *p, int n)
{
    int fOld, fNew;
    if (p->n190 == n) return;
    fOld = !((unsigned)(p->n190 + 1) < 2);
    fNew = !((unsigned)(n + 1) < 2);
    if (fOld != fNew) {
        if (fNew) {
            VCALL(p->p2C0, 56);
            func_00262450(p->p2C0, 0x3CA);
            func_00262450(p->p2C0, 0x3D2);
            func_0026D7B0(p, 1);
        } else
            VCALL(p->p2C0, 54);
    }
    if (p->n190 == 5) {
        func_00240DB0(p);
        p->f1E0 = 0;
    }
    p->n190 = n;
    p->f194 = g_clock.t;
    switch (n) {
    case 0:
        VCALLQ(p, 40, D_00317560);
        VCALLQ(p, 41, D_00317560);
        break;
    case 1:
        func_00262450(p->p2C0, 0x3EF);
        break;
    case 2:
        VCALLQ(p, 40, D_00317560);
        VCALLQ(p, 41, D_00317560);
        func_00167960(func_001F4A80(p), 1.1f);
        func_00166A40(func_001F4A80(p));
        if (p->p1D8) func_00225EE8(p->p1D8, p);
        func_00137588(p->p2A4, p, 9, &p->p2B0, 0.0f, 1.0f);
        func_00262450(p->p2C0, 0x3F0);
        break;
    case 3:
        func_00262450(p->p2C0, 0x3F1);
        break;
    case 4:
        func_00167960(func_001F4A80(p), 1.4f);
        func_00166A40(func_001F4A80(p));
        if (p->p1D4) func_00225EE8(p->p1D4, p);
        func_00137588(p->p27C, p, 9, &p->p2B0, 0.0f, 1.0f);
        break;
    case 5:
        func_00137628(&p->p2BC);
        func_00137628(&p->p2B8);
        func_00137628(&p->p2B4);
        func_00137588(p->p2A8, p, 1, &p->p2B0, 0.0f, 1.0f);
        func_001854C8(D_0036C700, 0xC, p);
        break;
    }
    func_0028F068(p, p->p48, (unsigned)(p->n190 - 1) <= 3 ? 2 : 1);
    func_0028F068(p, p->p4C, (unsigned)(p->n190 - 1) <= 3 ? 2 : 1);
    {
        int f;
        if (p->n190 == 1 || p->n190 == 4) f = 0; else f = 1;
        func_0023EBF8(p, f);
    }
}
/* next data of this unit's .rodata block after the jump table (used by func_0026D470) */
extern const float D_00328B48[2] = { -0.8f, 0.8f };
