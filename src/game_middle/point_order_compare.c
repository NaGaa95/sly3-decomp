// SLY3_CFLAGS: -Os -G0
struct QuadPoint { float x, y, z, w; };
int func_001E7C30(const struct QuadPoint *a, const struct QuadPoint *b)
{
    if (a->x > b->x) return 1;
    if (a->x < b->x) return -1;
    if (a->y > b->y) return 1;
    if (a->y < b->y) return -1;
    return a - b;
}
