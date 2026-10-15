// Reference algorithm: src/hand/func_001A3EE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x4988]; void *a[256]; int x4554; int x4558, x455c; int x4560; void *x4564; int x4568; char x4570[0x20]; };
void func_00292034(void *p, int c, int n);
void func_001C5C18(struct S *s, void *p);
void func_001C5E08(struct S *s)
{
    unsigned int i;
    if (s->x4554) {
        s->x4554 = 0;
        func_00292034(s->x4570, 0, 0x20);
        func_00292034(s->x4564, 0, s->x4560 << 5);
        for (i = 0; i < 0x100; i++) {
            if (s->a[i])
                func_001C5C18(s, s->a[i]);
        }
    }
}
