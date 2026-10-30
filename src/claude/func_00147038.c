// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void (*call)(void *); };
struct Obj { char pad[0xC]; struct VirtualEntry *table; };
struct S { char pad[0x314]; int c; struct Obj *a[2]; };
void func_00147038(struct S *s)
{
    int i;
    for (i = 0; i < s->c; i++) {
        struct Obj *o = s->a[i];
        if (o)
            o->table[9].call((char *)o + o->table[9].delta);
    }
    s->c = 0;
}
