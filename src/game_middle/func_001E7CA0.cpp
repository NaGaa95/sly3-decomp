// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sorts the n points (qsort-style helper func_00292540, 16-byte elements, ordered by func_001E7C30), then builds their
// convex hull with the monotone chain method: the first pass walks the points forwards and removes the middle point
// whenever the last three hull points turn the wrong way (negative cross product z), the second pass walks them
// backwards down to the point at the end of the first chain. The hull lives in a temporary 0x800-byte block (scoped by
// the func_001D2770 / func_001D2798 pair) and at most 32 points are copied to p->a (count in p->c).
// Matching notes: each pass has its own counter (i, j); the turn test passes the middle point as both the head of the
// second edge and the tail of the first one, so it is loaded once per edge operand.
typedef int qword __attribute__((mode(TI)));
struct CTX { int words[4]; };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct P { char pad0[0xD8]; int c; char pad1[0xE4 - 0xDC]; qword *a; };
struct QuadPoint { float x, y, z, w; };

extern "C" {
void func_00292540(void *base, int n, int cb, int (*cmp)(const void *, const void *));
void func_001D2770(CTX *);
void *func_001D25B0(const AREQ &);
void func_001D2898(void *dst, const void *src, int cb);
void func_001D2798(CTX *, int);
int func_001E7C30(const QuadPoint *, const QuadPoint *);
}

static inline void *Alloc(int cb) { AREQ r(cb, 0x10); return func_001D25B0(r); }
// z component of the cross product (b - a) x (c - d)
static inline float CrossZ(const qword &a, const qword &b, const qword &c, const qword &d)
{
    qword e, f, r;
    float z;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(e) : "j"(b), "j"(a));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(f) : "j"(c), "j"(d));
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(e), "j"(f));
    __asm__("qmfc2.ni %0, %1\n\tpextuw %0, $0, %0" : "=r"(z) : "j"(r));
    return z;
}

extern "C" void func_001E7CA0(P *p, int n, qword *pts)
{
    int i, j, k, t;
    qword *hull;
    func_00292540(pts, n, 0x10, (int (*)(const void *, const void *))func_001E7C30);
    k = 2;
    {
        CTX ctx;
        func_001D2770(&ctx);
        hull = (qword *)Alloc(0x800);
        func_001D2898(hull, pts, 0x20);
        for (i = 2; i < n; i++) {
            hull[k++] = pts[i];
            while (k >= 3) {
                if (CrossZ(hull[k - 3], hull[k - 2], hull[k - 1], hull[k - 2]) < 0.0f) {
                    hull[k - 2] = hull[k - 1];
                    k--;
                } else
                    goto LBL;
            }
            LBL:;
        }
        t = k;
        hull[k++] = pts[n - 2];
        for (j = n - 3; j >= 0; j--) {
            hull[k++] = pts[j];
            while (t < k) {
                if (CrossZ(hull[k - 3], hull[k - 2], hull[k - 1], hull[k - 2]) < 0.0f) {
                    hull[k - 2] = hull[k - 1];
                    k--;
                } else
                    goto LBL2;
            }
            LBL2:;
        }
        {
            int cMax = 32;
            p->c = (k > cMax - 1) ? cMax : k;
        }
        func_001D2898(p->a, hull, p->c << 4);
        func_001D2798(&ctx, 2);
    }
}
