// Convert a control direction into an eight-way selection above the activation threshold; clear the selection below the release threshold.
// Reference algorithm: src/hand/func_001DA858.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct OBJ OBJ;
typedef struct { short d; short pad; void (*pfn)(void *, int); } VTE;
typedef struct {  float x; float y; float g; } Q;
struct OBJ {
    char pad[0xC];
    VTE *vt;
    char unknown10[0xC]; Q *q;
    char pad14[0x38 - 0x20];
    int n;
};
float func_002A3EE8(float, float);
void func_0021EC30(OBJ *p)
{
    Q *q = p->q;
    int n;
    float g;
    if (q == 0)
        return;
    n = p->n;
    g = q->g;
    if (n == -1) {
        if (0.8f < g) {
            int k = (int)(func_002A3EE8(q->y, q->x) * 1.2732395f + 8.5f);
            p->vt[14].pfn((char *)p + p->vt[14].d, k % 8);
        }
    } else if (g < 0.5f) {
        p->vt[14].pfn((char *)p + p->vt[14].d, -1);
    }
}
