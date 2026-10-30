// SLY3_CFLAGS: -Os -G0
void *func_001F1E18(void *p);
int func_0013B500(void *p, int k);
void func_00154EF0(void *s, void *a, void *o, int n);
struct S { char pad[0x11B4]; void *a; char pad2[0x1458 - 0x11B8]; void *o; void *b; };
void func_00156DC0(struct S *s)
{
    void *o;
    if (!s->a)
        return;
    o = func_001F1E18(s->a);
    if (o && !func_0013B500(o, 0x67) && !func_0013B500(o, 0x69) && s->b) {
        s->o = o;
        func_00154EF0(s, s->b, o, -1);
    }
}
