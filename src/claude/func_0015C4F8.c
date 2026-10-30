// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void (*call)(void *); };
struct S { char pad[0x5C]; int n; int a[34]; char pad2[0xEC - 0x60 - 34*4]; struct VirtualEntry *table; };
void func_00291F38(void *d, void *s, int n);
void func_0015C4F8(struct S *s, int x)
{
    int removed = 0;
    int i;
    for (i = 0; i < s->n; i++) {
        int *p = &s->a[i];
        if (*p == x) {
            func_00291F38(p, &s->a[i + 1], (s->n - i) * 4 - 4);
            s->n--;
            i--;
            removed = 1;
        }
    }
    if (removed)
        s->table[6].call((char *)s + s->table[6].delta);
}
