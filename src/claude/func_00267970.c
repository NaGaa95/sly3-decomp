// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { char pad[0x10]; int f; void *p; };
struct S { char pad[8]; struct E *ae; };
void func_00244C28(void *p);
void func_00267970(struct S *p, int i)
{
    p->ae[i].f = 1;
    {
        register void *q __asm__("$2") = p->ae[i].p; /* pin: the sound pointer is read into v0 */
        if (q)
            func_00244C28(q);
    }
}
