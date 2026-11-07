// SLY3_CFLAGS: -Os -G0
// Pause (f != 0: clear +0x5E, func_00244C70) or dirty-flag a sound, then its vtable slot 2.
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct S { char pad[0xC]; struct VTE *vt; char pad10[0x5E - 0x10]; short n5E; };
void func_00244C70(struct S *p);
void func_00245320(struct S *p, int a, int b);
typedef int DI __attribute__((mode(DI)));
void func_00246AC8(int f, DI x)
{
    struct S *p = (struct S *)(int)x;
    if (f) {
        p->n5E = 0;
        func_00244C70(p);
    } else {
        func_00245320(p, 0x1000, 0x1000);
    }
    p->vt[2].pfn((char *)p + p->vt[2].delta);
}
