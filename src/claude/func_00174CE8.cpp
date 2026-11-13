// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// SortRpl: bucket the render list by kind (Sly 2 counterpart func_00157AE0, reworked in Sly 3): count kinds and groups,
// add an empty placeholder entry for each world group whose two kinds are absent, prefix-sum into aiFirst/ac, scatter
// into aprpl, then qsort the buckets of the five sorted kinds of every active group plus kind 0x90.
// Matching notes: the two counting loops are do-whiles (no LOOP_VTOP note, so loop.c can't reverse them); one RPL *p
// shared by loops 1-3 keeps the pointer non-replaceable (the s0 copy) and makes cse express the giv step as p + 16;
// the inner loop bound is a sizeof expression (sltiu).
struct RPL { int k; float z; unsigned int a8; unsigned int aC; };
struct GAMEW { unsigned char pad[0x3EB8]; int c3EB8; };
extern "C" {
extern GAMEW D_00475480;
extern int D_00479338;
extern int D_00321170[5];
void *func_00292034(void *, int, int);
void func_00292540(void *, int, int, int (*)(const void *, const void *));
int func_00175070(int k);
int func_00174FF0(int a, int b);
int func_00174FF8(int a, int b);
int func_00175098(int k);
int func_00174C58(const void *, const void *);
int func_00174CA0(const void *, const void *);
}
extern "C" int func_00174CE8(int c, int cMax, RPL *arpl, RPL **aprpl, int *aiFirst, int *ac)
{
    int acGroup[14];
    int ai[0xE0];
    int i;
    RPL *p;
    func_00292034(acGroup, 0, sizeof(acGroup));
    func_00292034(ac, 0, 0xE0 * 4);
    i = 0;
    if (c > 0) do {
        p = &arpl[i];
        ac[p->k]++;
        acGroup[func_00175070(p->k)]++;
    } while (++i < c);
    for (i = 0; i < D_00475480.c3EB8; i++) {
        int a = func_00174FF0(1, i);
        int b = func_00174FF0(5, i);
        if (acGroup[a] == 0 && acGroup[b] == 0 && c < cMax) {
            p = &arpl[c++];
            func_00292034(p, 0, sizeof(RPL));
            int k = func_00174FF8(2, b);
            p->k = k;
            ac[k]++;
        }
    }
    {
        int j;
        int t = 0;
        for (j = 0; j < 0xE0; j++) {
            aiFirst[j] = t;
            ai[j] = t;
            t += ac[j];
            ac[j] = t;
        }
    }
    i = 0;
    if (c > 0) do {
        p = &arpl[i];
        aprpl[ai[p->k]++] = p;
    } while (++i < c);
    {
        int g;
        for (g = 0; g < 14; g++) {
            if (g == 0 || g == 9)
                continue;
            if (func_00175098(g) >= D_00479338)
                continue;
            for (i = 0; i < sizeof(D_00321170) / sizeof(D_00321170[0]); i++) {
                int k = func_00174FF8(D_00321170[i], g);
                func_00292540(aprpl + aiFirst[k], ac[k] - aiFirst[k], 4, func_00174C58);
            }
        }
    }
    func_00292540(aprpl + aiFirst[0x90], ac[0x90] - aiFirst[0x90], 4, func_00174CA0);
    return c;
}
