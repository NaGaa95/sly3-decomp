// SLY3_CFLAGS: -Os -G0 -fno-strength-reduce
// func_0015D510: compare loop written as while (ids[i] == a[i]) { if (++i >= n) goto same; }
// so jump1 duplicates the compare as in the target; -fno-strength-reduce keeps the indexed loads; table loaded after CopyAb.
struct VirtualEntry { short delta, reserved; void (*call)(void *, int, int, int, int, int); };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
void func_0015C178(void *s, int state);
int func_0015D2F0(void *p, int max, int *ids);
int func_0015D2D8(const void *a, const void *b);
void func_00292540(void *base, int n, int size, int (*cmp)(const void *, const void *));
void CopyAb(void *dst, void *src, int n);

void func_0015D510(char *p)
{
    int st = *(int *)(p + 0x120);
    int ids[64];
    int n;
    int i;
    if (st == 2) {
        float t = *(float *)(p + 0x128);
        if (0.0f <= t && t < g_clock.t - *(float *)(p + 0x124))
            func_0015C178(p + 0x120, 1);
        return;
    }
    if (st >= 3)
        return;
    if (st < 0)
        return;
    n = func_0015D2F0(p, 0x40, ids);
    if (*(int *)(p + 0x244)) {
        int changed = 0;
        func_00292540(ids, n, 4, func_0015D2D8);
        if (*(int *)(p + 0x23C) != n) {
            changed = 1;
        } else {
            i = 0;
            if (n > 0) {
            while (ids[i] == (*(int **)(p + 0x240))[i]) {
                if (++i >= n)
                    goto same;
            }
            changed = 1;
            }
        same:;
        }
        if (changed) {
            struct VirtualEntry *table;
            *(int *)(p + 0x23C) = n;
            CopyAb(*(void **)(p + 0x240), ids, n * 4);
            table = *(struct VirtualEntry **)(p + 0xC);
            table[3].call(p + table[3].delta, 9, 0, 0, 0, 0);
        }
    }
    if (n > 0) {
        *(int *)(p + 0x134) = ids[0];
        func_0015C178(p + 0x120, 1);
    } else {
        *(int *)(p + 0x134) = 0;
        func_0015C178(p + 0x120, 0);
    }
}
