// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0015A600: port of Sly 2 func_001477D8 (HUD 2-matrix GIF sprite draw). Owns rodata 0x320780-0x32082F.
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct VECTOR4F { float x, y, z, w; };
struct M4 { qword r[4]; };
struct GIFS { int a[16]; };
struct TEX { char pad[0x4]; int x4; int x8; char padC[0x30 - 0xC]; ulong ul30; ulong pad38; ulong ul40; };
struct RGBA { unsigned char r, g, b, a; };
struct X { char pad[0x24]; void *x24; char pad2[0x30 - 0x28]; int x30; };
struct P { char pad[0x50]; void *p50; char pad2[0x130 - 0x54]; int x130; int pad134; char *ap138[2]; int pad140; int x144; int x148; int x14C; };
extern "C" {
extern struct X *D_0036C328;
extern void *D_0036C314;
extern struct GIFS D_0036C2E0;
extern struct TEX D_0036DBE0;
extern struct RGBA D_0036BC44;
extern char D_0036E680[];
void func_0015A1E8(struct P *p);
void func_0015A038(struct P *p, int n);
void func_00195808(struct RGBA *prgba, void *pv, int n, struct GIFS *pgifs);
void func_0018CA08(struct GIFS *pgifs, int a, int b, int c);
void func_0018CCC0(struct GIFS *pgifs, int reg, ulong val);
int func_002BC640(struct TEX *ptex, int n);
int func_002BC648(struct TEX *ptex, int n);
int func_002BC668(struct TEX *ptex, int n);
int func_002BC670(struct TEX *ptex, int n);
void func_0028EC08(struct M4 *pm, int n, void *p, void *q);
void func_0018CB68(struct GIFS *pgifs, float s, float t, float q);
void func_0018CAA0(struct GIFS *pgifs, int rgba);
void func_0018CBD0(struct GIFS *pgifs, int x, int y, int z);
}
static const float s_aduv[2][2] = { { 0.0f, 0.0f }, { 0.00048828125f, 0.0f } };
static const VECTOR4F s_apos[4] = { { -0.5f, 0.5f, 0.0f, 1.0f }, { -0.5f, -0.5f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.5f, -0.5f, 0.0f, 1.0f } };
static const float s_auv[4][2] = { { 0.0f, 0.0f }, { 0.0f, 0.0009765625f }, { 0.00048828125f, 0.0f }, { 0.00048828125f, 0.0009765625f } };
static const struct VECTOR4F s_mClip[4] = { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, -0.5f }, { 0.0f, 0.0f, 0.0f, 1.0f } };

union VECTOR4 { qword q; float f[4]; };
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(qword a) { q = a; } VU_VECTOR(const VECTOR4 &v) { q = v.q; } };
struct VU_VECTOR4 { qword q; VU_VECTOR4() {} VU_VECTOR4(qword a) { q = a; } VU_VECTOR4(const VECTOR4F &v) { q = *(qword *)&v; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
VU_VECTOR4 operator*(const M4 &m, VU_VECTOR4 v) __asm__("func_0011D598");
static inline qword operator*(VU_FLOAT f, VU_VECTOR v)
{ qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v.q)); return r; }
static inline void SetStq(GIFS *pgifs, const float &s, const float &t, const float &q) { func_0018CB68(pgifs, s, t, q); }
static inline void SetRgba(GIFS *pgifs, const int &rgba) { func_0018CAA0(pgifs, rgba); }
static inline void SetXyz(GIFS *pgifs, const int &x, const int &y, const int &z) { func_0018CBD0(pgifs, x, y, z); }
static inline float Screen(const float &g, const float &s) { return (g + 0.5f) * s + 0.5f; }

extern "C" void func_0015A600(struct P *p)
{
    struct RGBA rgba;
    struct M4 am[2];
    float rw;
    unsigned int i;
    int state;
    switch (p->x130) {
    case 1:
        func_0015A1E8(p);
        func_0015A038(p, 2);
        break;
    case 2:
    case 3:
        break;
    default:
        return;
    }
    D_0036C328->x30 &= ~1;
    if (!D_0036C328->x24)
        D_0036C328->x24 = D_0036C314;
    rgba = D_0036BC44;
    func_00195808(&rgba, D_0036E680, 1, &D_0036C2E0);
    func_0018CA08(&D_0036C2E0, 0, 1, 0xE);
    {
    struct TEX *ptex = &D_0036DBE0;
    func_0018CCC0(&D_0036C2E0, 0x47, 0x31001);
    func_0018CCC0(&D_0036C2E0, 6, ((ulong)(int)(ptex->ul40 & 0x1FF) << 5) | (((ptex->ul30 >> 16) & 0x3F) << 14) | 0x6A8000000UL);
    func_0018CCC0(&D_0036C2E0, 0x14, 0x61);
    func_0018CCC0(&D_0036C2E0, 0x3F, 0);
    {
        int w = func_002BC640(ptex, ptex->x4);
        int h = func_002BC648(ptex, ptex->x8);
        func_0018CCC0(&D_0036C2E0, 8, 0xA | ((ulong)w << 14) | ((ulong)h << 34));
    }
    }
    for (i = 0; i < 2; i++) {
        struct M4 m;
        func_0028EC08(&m, 0, p->p50, p->ap138[i] + 0x40);
        am[i] = m;
    }
    state = 0;
    do {
        switch (state) {
        case 0:
            if (!p->x144 || !p->x14C)
                goto next;
            break;
        case 1:
            if (!p->x148)
                goto next;
            break;
        case 2:
            if (!p->x144 || p->x14C)
                goto next;
            break;
        }
        {
            i = state & 1;
            unsigned int j;
            func_0018CA08(&D_0036C2E0, 0x14, 3, 0x512);
            for (j = 0; j < 4; j++) {
                VECTOR4 u;
                struct TEX *ptex = &D_0036DBE0;
                int off = 0x800;
                u.q = (*(const M4 *)s_mClip * (am[i] * VU_VECTOR4(s_apos[j]))).q;
                rw = 1.0f / u.f[3];
                u.q = VU_FLOAT(rw) * VU_VECTOR(u);
                u.f[0] = Screen(u.f[0], (float)func_002BC640(ptex, ptex->x4));
                u.f[1] = Screen(u.f[1], (float)func_002BC648(ptex, ptex->x8));
                SetStq(&D_0036C2E0, rw * (float)func_002BC640(ptex, ptex->x4) * (s_auv[j][0] + s_aduv[i][0]),
                       rw * (float)func_002BC648(ptex, ptex->x8) * (s_auv[j][1] + s_aduv[i][1]), rw);
                SetRgba(&D_0036C2E0, 0x80808080);
                int x = (int)u.f[0];
                int xx = func_002BC668(ptex, x + (off - func_002BC640(ptex, ptex->x4) / 2));
                int y = (int)u.f[1];
                SetXyz(&D_0036C2E0, xx, func_002BC670(ptex, y + (off - func_002BC648(ptex, ptex->x8) / 2)), 0);
            }
        }
    next:
        state++;
    } while (state < 3);
}
