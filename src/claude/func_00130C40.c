// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct A { char pad[0x118]; float f; };
struct B { struct A *pa; };
extern void func_00167960(struct A *pa, float f);
void func_00130C40(char *p, float f)
{
    struct B *pb = *(struct B **)(p + 0xD0);
    if (pb) {
        if (f == 0.0f)
            f = pb->pa->f;
        func_00167960(pb->pa, f);
    }
}
