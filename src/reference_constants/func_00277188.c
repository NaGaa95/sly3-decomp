// Reference algorithm: src/hand/func_002241D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(); };
struct O { int a[3]; struct VTE *vt; char pad[0x120]; int k; };
struct Q { int a; struct O *o; };
void func_0013BEC0(struct O *p, int k, struct Q *q);
void func_00277188(struct O *p, int k, struct Q *q)
{
    func_0013BEC0(p, k, q);
    if (k == 6) {
        struct O *o = q->o;
        if (o == p && (unsigned)(o->k - 1) < 2) o->vt[80].pf((char *)o + o->vt[80].d, 3);
    }
}
