// SLY3_CFLAGS: -Os -G0
struct E { int id; char pad[0x28]; };
struct S { char pad[0x130]; int n; struct E *a; struct E *cur; };
void func_0014DBB8(struct S *s, int id)
{
    int i;
    for (i = 0; i < s->n; i++) {
        struct E *e = &s->a[i];
        if (id == e->id) {
            s->cur = e;
            return;
        }
    }
    s->cur = s->a;
}
