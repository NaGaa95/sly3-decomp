// SLY3_CFLAGS: -Os -G0
// f == 0: vtable slot 6; else dirty-flag the sound with 0x1FF or 0x3FF depending on its kind (slot 7 == 2).
struct VTE { short delta; short pad; int (*pfn)(void *); };
struct S { char pad[0xC]; struct VTE *vt; };
void func_00245320(struct S *p, int a, int b);
void func_00245EE0(struct S *p, int f)
{
    if (!f) {
        p->vt[7].pfn((char *)p + p->vt[7].delta);
        return;
    }
    {
        int grf = 0x1FF;
        if (p->vt[8].pfn((char *)p + p->vt[8].delta) != 2)
            grf = 0x3FF;
        func_00245320(p, grf, 8);
    }
}
