// Reference algorithm: src/hand/func_0015C150.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
struct P { int a; int b; float f; float g; qword q; qword r; qword s; };
void func_002333B4(void *pv, int b, int cb);
void func_00179E10(struct O *o)
{
    struct P p = {0};
    struct VTE *vt;

    vt = o->vt;
    vt[55].pfn((char *)o + vt[55].d, &p);
}
