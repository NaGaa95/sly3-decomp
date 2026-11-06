// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of the Sly 2 source src/hand/func_001F8668.c (flag bit 3 at +0x128, recursive over children).
typedef unsigned long ulong;
struct L { char pad[0x24]; struct L *next; char pad2[0x54 - 0x28]; struct L *first; char pad2b[0x128 - 0x58]; ulong lo : 3; unsigned int b35 : 1; ulong hi : 60; };
struct G { char pad[0x45E0]; int f; };
extern struct G D_00475480;
void func_00211F90(struct L *);
void func_00211F18(struct L *);
int func_0013B500(void *, int);
void func_00241F00(struct L *p, int f)
{
    struct L *q;
    if (f != p->b35) {
        p->b35 = f;
        if (D_00475480.f) {
            if (f) func_00211F90(p);
            else func_00211F18(p);
        }
        for (q = p->first; q; q = q->next)
            if (func_0013B500(q, 0x2F)) func_00241F00(q, f);
    }
}
