// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VEntry { short delta; short pad; void (*fn)(void *); };
struct S { char pad[0xC]; struct VEntry *table; char pad2[0x118 - 0x10]; float g118; float g11C; int x120; };
void func_00167960(struct S *p, float g)
{
    int f = __builtin_fabsf(g - p->g118) > 1e-4f;
    p->g118 = g;
    p->g11C = g;
    p->x120 = 0;
    if (f)
        p->table[55].fn((char *)p + p->table[55].delta);
}
