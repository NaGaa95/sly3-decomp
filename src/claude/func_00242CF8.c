// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ulong __attribute__((mode(DI)));
struct VT { short d; short pad; int (*pfn)(void *); };
struct O { char pad[0xC]; struct VT *pvt; };
struct S { char pad[8]; struct O *po; char pad2[0x9C - 0xC]; int k; char pad3[0xA8 - 0xA0]; int i; struct S *pNext; };
struct X;
struct L { struct S *ps; struct L *pNext; char pad[4]; struct X *px; };
struct E { char pad[0x64]; struct L *pl; struct S *ps; };
struct X { char pad[0xDC]; struct E *pe; char pad2[0x120 - 0xE0]; ulong fl; };

int func_00242CF8(int a, int b, int c, struct X **apx, int cMax, struct S **aps)
{
    int i;
    int cs = 0;
    for (i = 0; i < c; i++) {
        struct X *px = apx[i];
        register struct L *pl asm("$18"); /* pin: list cursor lives in s2 */
        px->fl |= ((ulong)1 << 60);
        pl = px->pe->pl;
        while (1) {
            struct S *ps;
        again:
            if (pl) {
                if (pl->px->fl & ((ulong)1 << 60)) { pl = pl->pNext; goto again; }
                ps = pl->ps;
            } else ps = px->pe->ps;
            for (; ps; ps = ps->pNext) {
                if (ps->k == 0xD) continue;
                if (ps->k == 0xE) {
                    struct O *po = ps->po;
                    if (!(po->pvt[96].pfn((char *)po + po->pvt[96].d) & 4)) continue;
                }
                if (cs >= cMax) return cs;
                ps->i = cs;
                aps[cs++] = ps;
            }
            if (!pl) break;
            pl = pl->pNext;
        }
    }
    return cs;
}
