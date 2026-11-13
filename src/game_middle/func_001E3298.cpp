// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Stretch along an axis: m1 * diag(s, 1/sqrt(s), 1/sqrt(s), 1) * inverse(m1), with m1 built from a basis around axis B and origin A.
// The zeroing goes through an inline helper: its pointer argument is substituted into the inlined call, so the stack address
// is computed straight into $a0 and recomputed for the later call (no CSE pseudo kept across the memset).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { M3 m; U pos; };
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
extern "C" {
extern qword D_00317530;
extern qword D_00317540;
void func_0011FEA8(qword a, qword b, qword c, qword *pm);
qword *func_002BA818(qword *pq, qword q);
void *func_00292034(void *destination, int byte, unsigned int bytes);
MATRIX4 func_0011D558(const MATRIX4 &a, const MATRIX4 &b);
MATRIX4 func_0011D768(const MATRIX4 &mat);
}
static inline void Clear(MATRIX4 *pmat) { func_00292034(pmat, 0, sizeof *pmat); }
static inline float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }

extern "C" void func_001E3298(qword origin, qword axis, MATRIX4 *out, float scale)
{
    M3 m;
    M4 m1;
    MATRIX4 stretch;
    m.r[0].q = axis;
    func_0011FEA8(axis, D_00317540, D_00317530, &m.r[1].q);
    M4 *pm = &m1;
    (void)func_002BA818(&m1.pos.q, origin);
    pm->m = m;
    m1.m.r[0].i[3] = m1.m.r[1].i[3] = m1.m.r[2].i[3] = 0;
    pm->pos.f[3] = 1.0f;
    Clear(&stretch);
    stretch.mat[0][0] = scale;
    float inv = 1.0f / SqrtF(scale);
    stretch.mat[2][2] = inv;
    stretch.mat[1][1] = inv;
    stretch.mat[3][3] = 1.0f;
    *out = func_0011D558(func_0011D558(*(MATRIX4 *)&m1, stretch), func_0011D768(*(MATRIX4 *)&m1));
}
