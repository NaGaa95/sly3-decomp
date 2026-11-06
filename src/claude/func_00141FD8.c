// SLY3_CFLAGS: -Os -G0
// func_00141FD8 (agent A43, from A7 wip): IsCur is (st == -1 || st == x430) (A7 had the != / && inverse);
// the third test is written out directly. -FLT_MAX literal D_0032000C belongs to func_00141580.c rodata.
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct Method { short delta, reserved; void (*call)(void *); };
struct O { unsigned char pad00[0xC]; struct Method *methods; };
struct S { char pad[0x430]; int x430; int pad434; int state; float t; int x440; int x444; struct O *o;
           int pad44C; char x450[0x20]; float x470; int pad474; int x478; char pad47C[0x4B4 - 0x47C]; float x4B4; };
extern const float D_0032000C; /* -FLT_MAX, defined with func_00141580's rodata */
void func_00162698(void *p, int n);
void func_00142650(struct S *s);
static inline int IsCur(struct S *s, int st)
{
    int r = 0;
    if (st == -1 || st == s->x430) {
        r = 1;
    }
    return r;
}
void func_00141FD8(struct S *s, int st)
{
    int old = s->state;
    int play;
    float rate;
    struct O *o;
    if (old == st)
        return;
    o = s->o;
    if (o) {
        if (IsCur(s, old) != IsCur(s, st)) {
            if (st == -1 || st == s->x430)
                o->methods[54].call((unsigned char *)o + o->methods[54].delta);
            else
                o->methods[56].call((unsigned char *)o + o->methods[56].delta);
        }
        old = s->state;
    }
    if (old >= 0x36 && (old < 0x39 || old == 0x3B))
        func_00162698(s->x450, -1);
    s->state = st;
    s->t = g_clock.t;
    s->x440 = 0;
    s->x444 = 0;
    play = 0;
    switch (st) {
    case 0x36:
        play = 1;
        rate = 2.5f;
        s->x444 = 2;
        break;
    case 0x37:
        play = 1;
        rate = 1.5f;
        s->x444 = 1;
        break;
    case 0x38:
        play = 1;
        rate = 3.0f;
        s->x444 = 1;
        break;
    case 0x39:
        s->x444 = 2;
        break;
    case 0x3A:
        s->x444 = 4;
        break;
    case 0x3B:
        play = 1;
        rate = 2.5f;
        s->x444 = 1;
        break;
    case 0x3C:
        s->x444 = 1;
        s->x4B4 = D_0032000C;
        break;
    case 0x3D:
        s->x444 = 3;
        break;
    }
    if (play) {
        s->x470 = rate;
        *(int *)s->x450 = s->x478;
        func_00162698(s->x450, 0);
    }
    func_00142650(s);
}
