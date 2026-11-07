// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct O { int a[3]; struct VTE *vt; char pad[0x40 - 0x10]; int x40; int x44; };
void func_001C8BF0(struct O *p, struct O *q);
void func_0028FE20(struct O *p, struct O *q)
{
    func_001C8BF0(p, q);
    q->vt[54].pf((char *)q + q->vt[54].d, q, &q->x40);
    p->vt[54].pf((char *)p + p->vt[54].d, q, &p->x40);
    p->x44 = -1;
}
