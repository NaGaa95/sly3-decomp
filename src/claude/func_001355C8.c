// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct M { short delta, pad; void (*fn)(void *); };
struct VT { char pad[0x40]; struct M m; };
struct Q { char pad[0xC]; struct VT *vt; char pad1[0x30 - 0x10]; int x30; char pad2[0x38 - 0x34]; int x38; int x3C; };
struct L { char pad[0x50]; float g50; float g54; };
struct X { char pad[0x29C]; char a29C[0x3D8 - 0x29C]; void *p3D8; char pad1[0x1080 - 0x3DC]; float g1080; };
struct P { char pad[0x10]; struct X *px; char pad1[0x18 - 0x14]; char a18[0x30 - 0x18]; int x30; int x34; float g38; struct L *p3C; };
void func_00238AE8(void *p);
void func_00238AB8(struct P *p);
float func_0011E940(float a, float b);
struct Q *func_00238690(void *p, int n);
void func_002566F0(void *p, int n);
extern const float D_0031F858; /* FLT_MAX, defined in func_00134BE8.c (same original unit) */
static inline void Method(struct Q *q) { struct M *m = &q->vt->m; m->fn((char *)q + m->delta); }
void func_001355C8(struct P *p, int st)
{
    if (st == p->x34)
        return;
    func_00238AE8(p->a18);
    if (p->x34 == 2) {
        float t = g_clock.t;
        t += func_0011E940(p->p3C->g50, p->p3C->g54);
        p->px->g1080 = t;
        p->p3C = 0;
    }
    p->x34 = st;
    p->g38 = g_clock.t;
    switch (st) {
    case 0: {
        struct Q *q = func_00238690(p->px->a29C, 0xC9);
        q->x3C = 0x11;
        Method(q);
        break;
    }
    case 1: {
        struct Q *q = func_00238690(p->px->a29C, 0xCA);
        q->x38 = p->x30;
        Method(q);
        break;
    }
    case 2: {
        struct Q *q = func_00238690(p->px->a29C, 0xD1);
        q->x30 = p->x30;
        q->x3C = (int)p->p3C;
        p->px->g1080 = D_0031F858;
        Method(q);
        func_002566F0(p->px->p3D8, 3);
        break;
    }
    case 3: {
        struct Q *q = func_00238690(p->px->a29C, 0xF2);
        q->x30 = p->x30;
        Method(q);
        break;
    }
    case -1:
        func_00238AB8(p);
        break;
    }
}
/* Next .rodata item of the original unit: a {2.0, 8.0} float pair (read via its address by func_00133B08 and
   func_00133EC0); it follows the jump table, so it is defined here for the table section to place. */
const float D_0031F878[2] = { 2.0f, 8.0f };
