// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
#define AT(p, off, type) (*(type *)((char *)(p) + (off)))
struct VTE { short d; short pad; void *fn; };
struct COMPONENT { VTE *vt; };
struct BINDING { int key; COMPONENT *component; };
struct MODEL { char pad[0x14]; void *table; char pad18[4]; float base; char pad20[0x20]; float scale; };
struct STATE { char pad[8]; float amount; };
struct VEC { float f[4]; };
struct SMP { float a, b, c; };
struct CLOCK { float t, dt; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
extern "C" {
extern CLOCK g_clock;
extern qword D_00317560;
extern const SMP D_003225E0;
extern const int D_003225F0[4];
float func_002A3EE8(float y, float x);
float func_0011E3B8(float g);
float func_0011E560(float g, float gMax);
float func_0011E438(void *p, float g);
float func_0011E730(const SMP *psmp, float *pvel, float cur, float vel, float target, float dt);
void func_001ACCA8(char *p);
void func_001AC098(char *p);
BINDING *func_00136EE0(void *table, char *p, int a, int b);
void func_001C2B48(void *p);
void func_001B1920(char *p);
void func_001B9C48(void *p);
void func_001B30E8(void *p);
void func_00140900(void *p);
void func_001C1888(char *p, void *q, int n, float a, float b);
void func_001ACE40(char *p);
int func_00173428(void *p);
void *func_00173408(void *p);
void func_00258CF0(void *p, float g);
void func_0024E878(char *p, float g);
void func_0024E920(char *p, int n);
void func_001AFF00(char *p);
MODEL *func_00156AB0(char *p);
qword func_0024F278(char *p, MODEL *m, float g);
void func_00138B68(MODEL *m, float g);
void func_001ADDD0(char *p, int a, int b);
void func_00148938(void *p);
void *func_002387A8(void *p, int n);
int func_001A7A80(STATE *s, int n, float g);
void func_0018C5A8(void *p, int n);
void func_001C0CB8(char *p);
int func_00138AC8(void *p);
void func_00137688(void *p);
void func_001AD1D0(char *p);
}
static inline float *Pos(char *p)
{
    VTE *e = &AT(p, 0xC, VTE *)[36];
    return ((float *(*)(void *))e->fn)(p + e->d);
}
static inline float Heading(char *p) { float *v = Pos(p); return func_002A3EE8(v[1], v[0]); }
static inline qword Scale(qword v, VU_FLOAT s) { qword d; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(v), "j"(s.q)); return d; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
static inline float Z(qword q) { float r; __asm__("pextuw %0, $0, %1" : "=r"(r) : "r"(q)); return r; }
static inline void ReadBinding(BINDING *b, MODEL *m, qword *out)
{
    COMPONENT *c = b->component;
    VTE *e = &c->vt[3];
    ((void (*)(void *, int, qword *, float, float))e->fn)((char *)c + e->d, 0, out, m->base, m->scale);
}
static inline bool FHas(char *p) { return AT(p, 0x1108, void *) && func_00173428(AT(p, 0x1108, void *)); }
void func_001AD1D0(char *p)
{
    func_0011E3B8(AT(p, 0x110C, float) - Heading(p));
    func_001ACCA8(p);
    func_001AC098(p);
    switch (AT(p, 0x19E0, int)) {
    case 0:
        break;
    case 5:
        {
            MODEL *m = AT(p, 0x113C, MODEL *);
            AT(p, 0x1A0, qword) = D_00317560;
            if (m) {
                BINDING *b = func_00136EE0(m->table, p, 1, 1);
                if (b) {
                    VEC v;
                    ReadBinding(b, m, (qword *)&v);
                    AT(p, 0x1A0, qword) = Scale(*(qword *)&v, VU_FLOAT(-1.0f));
                }
            }
            func_001C2B48(p + 0xE40);
        }
        break;
    case 4:
        func_001B1920(p);
        break;
    case 3:
        func_001B9C48(p + 0x320);
        break;
    case 8:
        func_001B30E8(p + 0x500);
        break;
    case 7:
        func_00140900(p + 0x1E90);
        break;
    case 10:
        func_001C1888(p, p + 0x1B20, AT(p, 0x1C20, int), AT(p, 0x110C, float), AT(p, 0x134, STATE *)->amount);
        break;
    case 11:
        func_001ACE40(p);
        break;
    case 1:
        {
            void *q = 0;
            if (FHas(p))
                q = func_00173408(AT(p, 0x1108, void *));
            func_00258CF0(q ? q : p + 0x1C90, AT(p, 0x134, STATE *)->amount);
            func_0024E878(p, AT(p, 0x110C, float));
        }
        break;
    case 6:
        switch (AT(p, 0x19E8, int)) {
        case 4:
            if (AT(p, 0x11B4, int))
                func_0024E920(p, AT(p, 0x11B4, int));
            break;
        case 5:
            func_001C1888(p, p + 0x1520, AT(p, 0x1620, int), AT(p, 0x110C, float), AT(p, 0x134, STATE *)->amount);
            break;
        }
        break;
    case 13:
        {
            MODEL *m = AT(p, 0x113C, MODEL *);
            if (m && m->table == AT(p, 0x1ABC, void *)) {
                func_001AFF00(p);
                break;
            }
            if (AT(p, 0x1D4C, int)) {
                BINDING *b = func_00136EE0(AT(p, 0x1AB8, void *), p, 1, 1);
                if (b) {
                    VEC v;
                    ReadBinding(b, AT(p, 0x113C, MODEL *), (qword *)&v);
                    AT(p, 0x1A0, qword) = Scale(*(qword *)&v, VU_FLOAT(-1.0f));
                }
            }
        }
        break;
    case 15:
        {
            MODEL *m = func_00156AB0(p);
            AT(p, 0x1A0, qword) = Scale(func_0024F278(p, m, m->base), VU_FLOAT(-1.0f));
        }
        break;
    case 16:
        {
            MODEL *m = func_00156AB0(p);
            AT(p, 0x1A0, qword) = Scale(func_0024F278(p, m, m->base), VU_FLOAT(-1.0f));
            func_00138B68(m, AT(p, 0x134, STATE *)->amount);
            func_0024E878(p, AT(p, 0x110C, float));
        }
        break;
    case 19:
        if (0.0f < AT(p, 0x134, STATE *)->amount)
            func_0024E878(p, AT(p, 0x110C, float));
        else
            func_0024E878(p, Heading(p));
        if (AT(p, 0x19E8, int) == 6 && 0.07f < g_clock.t - AT(p, 0x19EC, float)) {
            if (__builtin_fabsf(func_0011E3B8(Heading(p) - AT(p, 0x1BC, float))) < 0.1f)
                func_001ADDD0(p, 0x13, 7);
        }
        if (AT(p, 0x19E8, int) == 7) {
            float one;
            float speed = AT(p, 0x204, float) * 0.08f;
            float r;
            VTE *e;
            one = 1.0f;
            e = &AT(p, 0xC, VTE *)[39];
            r = func_0011E560(Z(((qword (*)(void *))e->fn)(p + e->d)) / speed, one);
            r = func_0011E730(&D_003225E0, (float *)(p + 0x1EF0), AT(p, 0x1EEC, float), AT(p, 0x1EF0, float), r * 0.8f, g_clock.dt);
            AT(p, 0x1EEC, float) = r;
            {
                float zero = 0.0f;
                AT(p, 0x1EC4, float) = GMax(zero, r);
                AT(p, 0x1EDC, float) = GMax(zero, -r);
            }
            AT(p, 0x1ED0, float) = one - __builtin_fabsf(r);
            func_00148938(AT(p, 0x1EE8, void *));
        }
        break;
    case 22:
        {
            void *q = func_002387A8(AT(p, 0x1454, char *) + 0x29C, 0xE7);
            if (q) {
                unsigned int i;
                for (i = 0; i < 4; i++) {
                    if (func_001A7A80(AT(p, 0x134, STATE *), D_003225F0[i], 0.15f))
                        func_0018C5A8(q, D_003225F0[i]);
                }
            }
        }
        break;
    case 24:
        switch (AT(p, 0x19E8, int)) {
        case 8:
            if (0.0f < AT(p, 0x134, STATE *)->amount)
                func_0024E878(p, func_0011E438(AT(AT(p, 0x1F20, char *), 0x284, void *), AT(p, 0x110C, float)));
            break;
        case 9:
            {
                MODEL *m = AT(p, 0x113C, MODEL *);
                AT(p, 0x1A0, qword) = Scale(func_0024F278(p, m, m->base), VU_FLOAT(-1.0f));
            }
            break;
        }
        break;
    }
    func_001C0CB8(p);
    if (AT(p, 0x13F8, void *) && func_00138AC8(AT(p, 0x13F8, void *))) {
        func_00137688(p + 0x13F8);
        AT(p, 0x13FC, int) = -1;
    }
}
