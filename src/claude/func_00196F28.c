// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Intersect two integer rectangles {left, top, right, bottom}; clears the output if empty.
void *memset(void *, int, unsigned int);
struct Rect { int left, top, right, bottom; };
static inline int GMax(int a, int b) { return a > b ? a : b; }
static inline int GMin(int a, int b) { return a < b ? a : b; }
int func_00196F28(struct Rect *a, struct Rect *b, struct Rect *out)
{
    out->left = GMax(a->left, b->left);
    out->top = GMax(a->top, b->top);
    out->right = GMin(a->right, b->right);
    out->bottom = GMin(a->bottom, b->bottom);
    if (out->left < out->right && out->top < out->bottom) {
        return 1;
    }
    memset(out, 0, sizeof(*out));
    return 0;
}
