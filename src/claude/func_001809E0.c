// SLY3_CFLAGS: -Os -G0
typedef struct { float x, y; } PAIR;
typedef struct {
    char pad[0x10];
    PAIR cur;
    int depth;
    PAIR stack[4];
} XFS;
static inline int ClampI(int v, int lo, int hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}
void func_001809E0(XFS *p)
{
    int n = --p->depth;
    PAIR *e = &p->stack[ClampI(n, 0, 3)];
    p->cur.x = e->x;
    p->cur.y = e->y;
}
