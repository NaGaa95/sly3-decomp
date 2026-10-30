// SLY3_CFLAGS: -Os -G0
struct E { int value; int enabled; };
struct VirtualEntry { short delta, reserved; void (*call)(void *); };
struct S { char pad[0x18]; int count; struct E entries[(0xEC - 0x1C) / 8]; struct VirtualEntry *table; };
void func_00291F38(void *dst, void *src, int n);

void func_0015C340(struct S *s, int key)
{
    int removed = 0;
    int i;
    for (i = 0; i < s->count; i++) {
        struct E *e = &s->entries[i];
        if (e->enabled && e->value == key) {
            func_00291F38(e, e + 1, (s->count - i) * 8 - 8);
            s->count--;
            i--;
            removed = 1;
        }
    }
    if (removed)
        s->table[6].call((char *)s + s->table[6].delta);
}
