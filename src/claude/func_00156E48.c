// SLY3_CFLAGS: -Os -G0
struct V { float a, b; int c; };
void func_00156E48(char *p, float f)
{
    struct V *v = (struct V *)(p + 0x440);
    v->a = f;
    v->b = f;
    v->c = 0;
}
