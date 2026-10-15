// Reference algorithm: src/hand/func_001FADD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0xD8]; int x; };
struct V { int x, y, z, w; };
qword func_00244740(struct S *, int, int);
void func_002449C8(struct S *p, int a, int b, struct V *pv)
{
    if (!p->x) { pv->z = 0; pv->y = 0; pv->x = 0; }
    else *(qword *)pv = func_00244740(p, a, b);
}
