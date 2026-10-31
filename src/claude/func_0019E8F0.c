// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00181EB0).
struct R { char pad[0xC]; int c; char dl[0xC]; };
struct Q { char pad[0x20]; struct R *pr; int n; float t; };
struct S { char pad[0x2B8]; char dl[0xC]; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern char D_0036C700[];
void func_00240DB0(void);
void func_0011B028(void *pdl, void *pv);
void func_0011AF60(void *pdl, void *pv);
void func_001854C8(void *g, int n, struct S *p);
void func_0019E5B8(struct S *p, struct R *r);
void func_0019E8F0(struct S *p, struct Q *q, int n)
{
    struct R *r;
    int old = q->n;
    if (n == old) return;
    if (old < 3) { if (old > 0) func_00240DB0(); }
    q->n = n;
    q->t = g_clock.t;
    if (n != 2) return;
    r = q->pr;
    r->c--;
    func_0011B028(r->dl, q);
    func_0011AF60(p->dl, q);
    if (!r->c) func_001854C8(D_0036C700, 0x4B, p);
    func_0019E5B8(p, r);
}
