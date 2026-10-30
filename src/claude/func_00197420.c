// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Entry { unsigned char pad[0xC]; int c; float g; int e; int off; };
struct Entry *func_00197628(void *self, int kind, int a);
void func_00197420(void *self, int a, int c, float g, int e, int on)
{
    struct Entry *entry = func_00197628(self, 7, a);
    entry->off = !on;
    entry->c = c;
    entry->e = e;
    entry->g = g;
}
