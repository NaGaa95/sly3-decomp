// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00221A18 (choose the zone entry and reset the follow state).
typedef int qword __attribute__((mode(TI)));
struct LM { float gMin, gMax; };
struct E { int x0; char pad[0x88 - 4]; struct LM lmTilt; };
struct T { char pad[0x108]; void *x108; int c; struct E *ae; char pad1[0x138 - 0x114]; int x138; float g13C; };
struct XF { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; struct XF *(*pf)(void *); };
struct CM { int a[3]; struct VTE *vt; char pad[0x11C - 0x10]; float g11C; char pad1[0x144 - 0x120]; float g144; };
struct R { char pad[0x5C]; float g5C; };
struct S { struct CM *cm; char pad[0x20 - 4]; struct T *pt; struct E *pe; void *pj; int pad2c; char a30[0xA0 - 0x30];
    float gA0, gA4, gA8, gAC; int xB0, xB4, xB8; char padbc[0xC4 - 0xBC]; float gC4; char aC8[0xE0 - 0xC8];
    float gE0, gE4; int xE8; char padec[0x100 - 0xEC]; qword pos; float g110, g114; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern struct E D_00349FB0;
extern float D_003290C8, D_003290CC;
struct T *func_001662A8(struct CM *pcm);
int func_0013B500(void *pj, int k);
int func_0013BEC8(int a, int b);
void func_00273A18(struct E *pe);
void func_001F3ED8(void *pj, int k, void *pv, void *pq);
void func_00273AB0(struct E *pe, void *pa, qword *pb, struct S *p);
void func_0022EA88(void *p, qword q, void *a, qword *pq, qword *b, float *c, void *pv);
void func_00120BA8(qword v, float *pa, float *pb, float *pc);
qword func_0011FDD8(float a, float b, float c);
void func_00166548(struct CM *pcm);
static __inline__ qword VAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ struct XF *Xf(struct CM *o) { return o->vt[36].pf((char *)o + o->vt[36].d); }
void func_002747D0(struct S *p)
{
    struct { qword a[6]; } q0;
    qword q60;
    qword q70;
    qword a;
    struct T *pt = func_001662A8(p->cm);
    p->pt = pt;
    p->gE4 = g_clock.t;
    p->xE8 = 1;
    if (!pt) {
        struct LM *plm = &D_00349FB0.lmTilt;
        plm->gMin = D_003290C8;
        plm->gMax = D_003290CC;
        p->pe = &D_00349FB0;
    } else {
        struct E *pe = pt->ae;
        int i;
        for (i = 1; i < p->pt->c; i++) {
            struct E *peT = &p->pt->ae[i];
            if (func_0013B500(p->pj, peT->x0) && func_0013BEC8(peT->x0, pe->x0))
                pe = peT;
        }
        p->pe = pe;
    }
    func_00273A18(p->pe);
    func_001F3ED8(p->pj, 1, p->a30, &q0);
    func_00273AB0(p->pe, &q0, &q60, 0);
    if (p->pt) {
        struct T *ptT = p->pt;
        if (ptT->x108)
            func_0022EA88(ptT->x108, q60, 0, &q70, 0, 0, p->aC8);
        func_00273AB0(p->pe, &q0, &q60, p);
    }
    a = VAdd(q60, q0.a[3]);
    func_00120BA8(VSub(Xf(p->cm)->pos, a), &p->gA0, &p->gA4, &p->gA8);
    p->gA8 = p->gA8 - p->cm->g144;
    p->pos = VAdd(a, func_0011FDD8(p->gA0, p->gA4, p->gA8));
    p->gAC = ((struct R *)p->pe)->g5C;
    p->xB0 = 0;
    if (p->pt && p->pt->x138)
        func_00166548(p->cm);
    p->g110 = p->g114 = g_clock.t;
    p->gE0 = g_clock.t;
    p->gC4 = g_clock.t - 10.0f;
    p->xB8 = 0;
    p->xB4 = 0;
    if (p->pt && p->pt->g13C != 0.0f)
        p->cm->g11C = p->pt->g13C;
}
