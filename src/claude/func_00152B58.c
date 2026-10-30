// SLY3_CFLAGS: -Os -G0
struct Q;
struct Method { short delta, reserved; void *call; };
struct Q { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x113C - 0x10]; struct Q *pNext; };
struct P { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x11B4 - 0x10]; int x11B4; int x11B8; unsigned char pad11BC[0x1444 - 0x11BC]; int x1444; };
extern struct Q *D_00479B5C;
/* FLT_MAX literal of this function; it is the .rodata item after D_00320548 in the original unit of
   func_00152218 (rodata 0x320540..0x32055F), so it is referenced by address here. */
extern const float D_00320554;
extern unsigned char D_00475480[];
int func_002548E0(struct Q *q, struct P *p, float *pd);
int func_0017E208(void *game, int a, int b, void *c, int n, struct Q **aq);
void func_00155380(struct P *p, struct Q *q, int *pk, float *pd, float *pd2);
void func_002BC5F0(void *buf, int n);

void func_00152B58(struct P *p)
{
    char buf[16];
    struct Q *aq[16];
    float d, d1, d2;
    float dBest, dBest2;
    int k1, k2, k;
    struct Q *q1, *q2, *q;
    if (p->x11B8)
        return;
    dBest2 = D_00320554;
    q2 = 0;
    q1 = 0;
    k2 = -1;
    k1 = -1;
    dBest = dBest2;
    for (q = D_00479B5C; q; q = q->pNext) {
        k = func_002548E0(q, p, &d);
        if (d < dBest) {
            dBest = d;
            k1 = k;
            q1 = q;
        }
        if (k2 < k || (k == k2 && d < dBest2)) {
            dBest2 = d;
            k2 = k;
            q2 = q;
        }
    }
    if (p->x1444) {
        int c = func_0017E208(D_00475480, 0x105, 0x33, 0, 16, aq);
        int i;
        for (i = 0; i < c; i++) {
            q = aq[i];
            if (q == p)
                continue;
            {
                func_00155380(p, q, &p->x11B4, &d1, &d2);
                k = 4;
                if (d1 < dBest) {
                    dBest = d1;
                    k1 = k;
                    q1 = q;
                }
                if (k2 < k || (k == k2 && d < dBest2)) {
                    dBest2 = d;
                    k2 = k;
                    q2 = q;
                }
            }
        }
    }
    ((void (*)(void *, int, struct Q *, int, struct Q *))p->methods[108].call)((char *)p + p->methods[108].delta, k1, q1, k2, q2);
    func_002BC5F0(buf, 2);
}
