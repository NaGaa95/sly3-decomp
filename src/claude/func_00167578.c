// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x80]; int n80; };
int func_00167578(void *p, struct S *ps)
{
    return ps->n80 > 0;
}
