// Convert a 64-bit timer to seconds, using the stored fallback duration only for an inactive empty resource.
// Reference algorithm: src/hand/func_001FE888.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct X { char pad[0x44]; int n40; char pad2[0x5C - 0x48]; unsigned short fl; unsigned short c52; char pad3[0x68 - 0x60]; ulong t; };
struct P { char pad[0x210]; struct X *px; char pad2[0x260 - 0x214]; float g24C; };
static inline float T(struct X *px) { return (float)px->t * (1.0f / 294912000.0f); }
float func_00248898(struct P *p)
{
    if (!p->px) return 0.0f;
    if (T(p->px) == 0.0f) {
        struct X *px = p->px;
        int f = 0;
        if (!px->n40) { f = px->c52 || (px->fl & 1); f ^= 1; }
        if (f) return p->g24C;
    }
    return T(p->px);
}
