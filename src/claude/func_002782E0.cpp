// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00225300 (state 5: hand the actor the source's basis, fade it in, then drop the prize).
typedef int qword __attribute__((mode(TI)));
typedef struct { short d, pad; void (*fn)(void *, ...); } VE;
struct M3 { qword r[3]; };
struct XF { M3 mat; qword pos; };
struct O { int a[3]; VE *vt; };
struct A { int a[3]; VE *vt; char pad10[0x29C - 0x10]; char a29C[0x11D8 - 0x29C]; void *color; };
struct R { char pad[0x30]; int state; };
struct S { int a[3]; VE *vt; char pad10[0x130 - 0x10]; int state; float time; char pad138[0x1D0 - 0x138]; O *source; A *actor; };
struct LM { float gMin, gMax; };
extern "C" {
extern struct CLOCK { float t, dt; } g_clock;
extern float D_00329280[3];
extern float D_00329290;
extern LM D_00341FF0;
extern char D_00475480[];
extern char D_0036C700[];
void func_00277030(S *);
R *func_002387A8(void *, int);
void func_0024E988(A *, const M3 *);
void func_0016D840(R *, int);
void func_0012F4F8(void *, qword);
void func_001F85F8(void *, int, qword, void *, int);
void func_001F4DD8(A *, S *, int, float);
void func_001854C8(void *, int, A *);
}
static inline XF *Xf(void *o) { O *b = (O *)o; XF *(*pf)(void *) = (XF *(*)(void *))b->vt[36].fn; return pf((char *)b + b->vt[36].d); }
static inline qword PosQ(void *o) { return Xf(o)->pos; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Length(qword d)
{
    qword one; float f;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}
static inline void Clamp(float *pg, LM *plm) { float gMax = plm->gMax, gMin = plm->gMin; if (*pg < gMin) *pg = gMin; else if (gMax < *pg) *pg = gMax; }
static inline qword Splat(float f)
{
    int b; qword r, t;
    __asm__("mfc1 %0,%1" : "=r"(b) : "f"(f));
    __asm__("pextlw %0,%2,%2\n\tpextlw %1,%0,%0" : "=r"(t), "=r"(r) : "r"(b));
    return r;
}
static inline void SetState(S *p, int k) { p->vt[80].fn((char *)p + p->vt[80].d, k); }
extern "C" void func_002782E0(S *p)
{
    int old;
    func_00277030(p);
    do {
        old = p->state;
        if (old == 5) {
            R *r;
            if (!p->actor) {
                SetState(p, 3);
            } else if (!(r = func_002387A8(p->actor->a29C, 0xD9)) || r->state == -1) {
                SetState(p, 2);
            } else {
                M3 m((p->source ? Xf(p->source) : Xf(p))->mat);
                func_0024E988(p->actor, &m);
                if (r->state != 4) {
                    qword pos = p->source ? PosQ(p->source) : PosQ(p);
                    qword other;
                    other = Xf(p->actor)->pos;
                    if (Length(Sub(pos, other)) < 100.0f)
                        func_0016D840(r, 4);
                }
                if (p->actor->color) {
                    float t = (g_clock.t - p->time) * 0.33333334f;
                    float g = D_00329280[0] + t * (D_00329280[1] + t * D_00329280[2]);
                    Clamp(&g, &D_00341FF0);
                    func_0012F4F8(p->actor->color, Splat(g));
                }
                if (3.0f < g_clock.t - p->time) {
                    func_001F85F8(D_00475480, 0x69, Xf(p->source)->pos, p, 1);
                    p->actor->vt[9].fn((char *)p->actor + p->actor->vt[9].d);
                    func_001F4DD8(p->actor, p, -1, D_00329290);
                    func_001854C8(D_0036C700, 0x10, p->actor);
                    SetState(p, 3);
                }
            }
        }
    } while (p->state != old);
}
