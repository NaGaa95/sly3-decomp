// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct VEntry { short delta; short pad; void *fn; };
struct LO { char pad[0xC]; struct VEntry *table; };
struct S { int x0; struct LO *plo4; int state; float tState; float t10; struct LO *p14; };
void func_00262280(struct LO *p, int k);
void func_00262450(struct LO *p, int k);
void func_00261580(struct LO *p, int k, float g);
void func_002643D0(struct LO *p, void *pv);
char *func_001F4A80(struct LO *p);
void func_00162698(struct S *p, int state)
{
    if (state == p->state)
        return;
    switch (p->state) {
    case 1:
        if (p->p14)
            func_00262280(p->p14, 0x3D8);
        break;
    case 2:
        if (p->p14) {
            func_00262280(p->p14, 0x3D5);
            func_00262280(p->p14, 0x3D6);
        }
        break;
    }
    p->state = state;
    p->tState = g_clock.t;
    switch (state) {
    case 1:
        p->t10 = g_clock.t;
        if (p->p14) {
            char *q;
            ((void (*)(void *, int))p->p14->table[53].fn)((char *)p->p14 + p->p14->table[53].delta, 0x3BE);
            q = func_001F4A80(p->plo4);
            if (q)
                func_002643D0(p->p14, q + 0x150);
            func_00262450(p->p14, 0x3D8);
            func_00261580(p->p14, 0x3D8, 0.0f);
        }
        break;
    case 2:
        if (p->p14) {
            func_00262450(p->p14, 0x3D5);
            func_00262450(p->p14, 0x3D6);
        }
        break;
    case -1:
    case 0:
        if (p->p14)
            ((void (*)(void *))p->p14->table[54].fn)((char *)p->p14 + p->p14->table[54].delta);
        break;
    }

}
