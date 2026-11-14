// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00277F20: state setter (0x130) - leaves the old state (CTX scope 0/4, 6 reset, -1 attach),
// enters the new one through a jump table (-1..6); its rodata (the per-state id table 0x8B..0x91 at 0x329240) is
// defined here in front of the jump table. Matching notes: Normalize is three VU asms (dot / sqrt / div) with an
// allocation-only extra "j"(v); the 0028E990 results enter the VU via the compiler's own qmtc2; no pins.
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { qword r[3]; };
struct VECTOR { float x, y, z; };
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct BONE { char pad[0x30]; qword pos; char pad40[0xA0 - 0x40]; void *pose; char padA4[0xB0 - 0xA4]; VECTOR v; };
struct O {
    char pad[0xC]; VTE *vt; char pad10[0x48 - 0x10]; BONE *bone48; BONE *bone4C; char pad50[0x130 - 0x50];
    int state; float tState; int n138; char pad13C[0x144 - 0x13C]; void *p144; void *p148; char pad14C[0x160 - 0x14C];
    void *task160; void *task164; char pad168[0x170 - 0x168]; qword q170; char pad180[0x188 - 0x180]; int n188;
};
struct CLOCK { float t, dt; };
extern "C" {
extern CLOCK g_clock;
extern char D_00475480[];
extern qword D_00317550;
void func_001309D8(void **);
void func_0013CD10(void *, O *);
void func_001C7A00(O *, int, int);
void func_0023AAE8(void *, O *, int, int, void **);
void func_0023AC58(void **);
void func_0023EBF8(O *, int);
void func_0023EC98(O *, int);
qword func_0011D3C0(const MATRIX3 *);
void *func_00130078(O *, BONE *, int, int, int, qword);
int func_00277680(O *);
qword func_0028E990(int, void *, qword);
MATRIX3 func_0011CBF0(qword, qword);
void func_002412C8(O *, float);
void func_00239DB8(void *, int);
}
extern const int D_00329240[7];
const int D_00329240[7] = { 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91 };
static inline void ClearV(VECTOR *pv) { pv->z = 0.0f; pv->y = 0.0f; pv->x = 0.0f; }
static inline qword Normalize(qword v)
{
    qword len, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(len), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(len));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(len), "j"(v));
    return r;
}
extern "C" void func_00277F20(O *p, int state)
{
    int old = p->state;
    if (state == old)
        return;
    p->state = state;
    p->tState = g_clock.t;
    p->n138 = -1;
    func_001309D8(&p->task164);
    func_001309D8(&p->task160);
    switch (old) {
    case 0:
    case 4:
        func_0013CD10(D_00475480, p);
        break;
    case 6: {
        p->n188 = 0;
        VTE *e = &p->vt[8];
        e->pf((char *)p + e->d);
        func_001C7A00(p, 0, 0x1F);
        break;
    }
    case -1:
        func_0023AAE8(p->p144, p, -1, 0, &p->p148);
        break;
    }
    switch (p->state) {
    case -1:
        func_0023AC58(&p->p148);
        func_001C7A00(p, 0, 0x1F);
        break;
    case 0: {
        func_0023EBF8(p, 0);
        func_0023EC98(p, 0);
        ClearV(&p->bone48->v);
        ClearV(&p->bone4C->v);
        qword pos = p->bone48->pos;
        qword rot = func_0011D3C0((MATRIX3 *)p->bone4C);
        p->task164 = func_00130078(p, p->bone48, 0, 8, 2, pos);
        p->task160 = func_00130078(p, p->bone4C, 0, 8, 2, rot);
        func_0013CD10(D_00475480, p);
        break;
    }
    case 2:
        func_0023EBF8(p, 1);
        func_0023EC98(p, 1);
        ClearV(&p->bone48->v);
        ClearV(&p->bone4C->v);
        if (func_00277680(p) && p->bone4C) {
            qword a = Normalize(func_0028E990(0, p->bone4C->pose, p->q170));
            qword b = Normalize(func_0028E990(0, p->bone4C->pose, D_00317550));
            MATRIX3 m;
            m = func_0011CBF0(a, b);
            p->task160 = func_00130078(p, p->bone4C, 0, 8, 2, func_0011D3C0(&m));
        }
        break;
    case 1:
        func_001C7A00(p, 0, 0x1F);
        func_0023EBF8(p, 0);
        func_0023EC98(p, 0);
        break;
    case 4:
        func_0013CD10(D_00475480, p);
        func_002412C8(p, 0.25f);
        break;
    case 3:
    case 5:
    case 6:
        break;
    }
    if (p->p148 && p->state >= 0)
        func_00239DB8(p->p148, D_00329240[p->state]);
}
