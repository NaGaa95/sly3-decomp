// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct P4 { char pad[0xA4]; void *pA4; };
struct S { void *p0; struct P4 *p4; char pad[0x10 - 8]; int x10; void *p14; };
extern int D_00349918[2];
extern int D_00349920[2];
extern char D_0036B118[];
void func_00147E08(void *, int, int, int *, int, int *, int *, struct P4 **);
void func_00258A10(struct S *, void *);
void func_00258958(struct S *p)
{
    if (p->p14) {
        func_00147E08(p->p0, 0x40, 2, &p->x10, 2, D_00349920, D_00349918, &p->p4);
        if (!p->p4->pA4)
            func_00258A10(p, D_0036B118);
    }
}
