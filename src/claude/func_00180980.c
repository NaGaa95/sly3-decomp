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
void func_00180980(XFS *p, float sx, float sy)
{
    int n = p->depth;
    PAIR *e = &p->stack[ClampI(n, 0, 3)];
    p->depth = n + 1;
    e->x = p->cur.x;
    e->y = p->cur.x;
    p->cur.x = p->stack[0].x * sx;
    p->cur.y = p->stack[0].y * sy;
}
