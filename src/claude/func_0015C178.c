// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void *(*call)(void *); };
struct Obj { char pad[0xC]; struct VirtualEntry *table; };
struct S { int state; float t; int pad8; int c; int d; char pad14[0xEC - 0x14]; struct VirtualEntry *table; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;

void func_0015C178(struct S *s, int state)
{
    int old = s->state;
    int enter, leave;
    if (old == state)
        return;
    enter = old == 0 && state == 1;
    leave = old != -1 && state == 0;
    s->state = state;
    s->t = g_clock.t;
    if (enter) {
        s->table[2].call((char *)s + s->table[2].delta);
        if (!s->c)
            func_0015C178(s, 2);
        if (s->d) {
            struct Obj *o = s->table[1].call((char *)s + s->table[1].delta);
            o->table[9].call((char *)o + o->table[9].delta);
        }
    }
    if (leave)
        s->table[3].call((char *)s + s->table[3].delta);
}
