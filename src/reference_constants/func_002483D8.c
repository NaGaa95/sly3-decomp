// Reference algorithm: src/hand/func_001FE3F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct Q { char pad[0x68]; ulong t; };
struct S { int c; struct Q *a[8]; };
struct P { char pad[0x214]; struct S s; };
float func_002483D8(struct P *p)
{
    struct Q *q;
    if (p->s.c > 0) { q = *(p->s.a + p->s.c - 1); }
    else q = 0;
    if (!q) return 0.0f;
    return (float)q->t * (1.0f / 294912000.0f);
}
