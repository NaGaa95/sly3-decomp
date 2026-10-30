// SLY3_CFLAGS: -Os -G0
struct PAIR { int id; int x4; };
struct SLOTS { int a, b; };
struct TRIPLE { int a, b, c; };
struct OWN { char pad[0xBC]; int a[10]; };
struct S0 {
    char pad[0x194]; struct OWN *po; int x198; int c; struct PAIR ap[3]; int x1B8; int aDefault[3]; int x1C8;
};
/* rodata at 0x00320CF0 / 0x00320D08 (not in symbol_addrs) */
const struct SLOTS D_00320CF0[3] = { { 0, 3 }, { 1, 4 }, { 2, 5 } };
const struct TRIPLE D_00320D08[4] = { { 0x3AE, 0x3AF, 0x3B0 }, { 0x3AE, 0x3AF, 0x3B0 }, { 0x3B1, 0x3B2, 0x3B3 }, { 0x3B4, 0x3B5, 0x3B6 } };
int func_001A9E90(int a);
void func_00260F18(struct OWN *po, int a, int b, int c);
void func_001633E0(struct S0 *p, int n);
void func_001634F0(struct S0 *p, int id, int n, struct PAIR *ap)
{
    int i;
    const struct TRIPLE *pt;
    if (!p->po) return;
    { unsigned int j; for (j = 0; j < 10; j++) p->po->a[j] = -1; }
    if (id != -1) p->po->a[9] = id;
    else p->po->a[9] = p->x1B8;
    p->c = 0;
    for (i = 0; i < n; i++) {
        *(struct PAIR *)((char *)p + p->c * 8 + 0x1A0) = ap[i];
        if (p->ap[p->c].id == -1) p->ap[p->c].id = p->aDefault[i];
        if (p->ap[p->c].id != -1) {
            const struct SLOTS *ps = &D_00320CF0[p->c];
            p->po->a[ps->a] = p->ap[p->c].id;
            p->po->a[ps->b] = func_001A9E90(p->ap[p->c].x4);
            p->c++;
        }
    }
    pt = &D_00320D08[p->x1C8 ? p->x1C8 : p->c];
    func_00260F18(p->po, pt->a, pt->b, pt->c);
    func_001633E0(p, 1);
}
/* Next .rodata items of the original unit (FLT_MAX literals read by later functions); they follow D_00320D08. */
const float D_00320D38 = 3.40282346638528859812e+38f;
const float D_00320D3C = 3.40282346638528859812e+38f;
