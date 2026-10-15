// Accumulate transition duration along the selected path using clamped polynomial speed and the active transition remainder.
// Reference algorithm: src/hand/func_001F11A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V3 { float x, y, z; float w; };
struct T { char pad[0x64]; float f74; float f78; char pad2[0x80 - 0x7C]; struct V3 v80; float f90; float f94; };
struct A { struct T *pt; int n4; int n8; int nC; };
struct Q { char pad[0x14]; struct T *pt; char pad2[0x1C - 0x18]; float f1C; char pad3[0x40 - 0x20]; float f40; };
struct P { char pad[0x24]; void *p24; char pad2[0x30 - 0x28]; struct Q *pq; int n34; char pad3[0x40 - 0x38]; struct A *pa; char pad4[0x48 - 0x44]; int n48; };
extern char D_0036BD20[];
int func_00239CC0(struct P *);
int func_00239AB8(void *, int);
struct A *func_0023A210(void *, int, int, int, int);
float func_00171C98(void *);
static inline float Eval(struct V3 *pv, float t)
{
    return pv->x + t * (pv->y + t * pv->z);
}
float func_0023A850(struct P *p, int k)
{
    float r = 0.0f;
    int end, cur;
    struct A *pa;
    if (func_00239CC0(p)) return r;
    end = func_00239AB8(p->p24, k);
    if (!p->pq) {
        cur = p->n34;
    } else {
        struct Q *pq = p->pq;
        if (!(p->pa->nC & 2)) {
            float d = pq->f40;
            float x;
            if (d < 0.0f) x = -pq->f1C;
            else if (0.0f < d) x = pq->pt->f74 - pq->f1C;
            else return r;
            r = x / d;
        }
        if (p->pa->n4 != p->n34) cur = p->pa->n4; else cur = p->pa->n8;
    }
    while (cur != end && (pa = func_0023A210(p->p24, p->n48, cur, end, 1)) != 0) {
        if (pa->pt) {
            float t = func_00171C98(D_0036BD20);
            float v = Eval(&pa->pt->v80, t);
            float mn = pa->pt->f90;
            float mx = pa->pt->f94;
            if (v < mn) v = mn;
            else if (mx < v) v = mx;
            r += pa->pt->f74 / (pa->pt->f78 * v);
        }
        if (pa->n4 != cur) cur = pa->n4;
        else cur = pa->n8;
    }
    return r;
}
