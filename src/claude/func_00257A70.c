// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct T { char pad[0x250]; int k; int pad254; void *p258; };
struct S { char pad[0x29C]; char a29C[0x1144 - 0x29C]; unsigned int n1144; };
extern char D_00475440[];
int func_002533C0(struct S *, int);
int func_00255D78(struct S *, void *, void *);
void *func_002579A0(struct S *, struct T *);
int func_00257CB0(void *);
void func_00238610(void *, int, struct T *);
void func_00257A70(struct S *p, struct T *t)
{
    unsigned int m;
    void *x;
    switch (t->k) {
    case 0:
        m = p->n1144 & 0x60;
        break;
    case 1:
        m = p->n1144 & 0x180;
        break;
    default:
        return;
    }
    if (!m)
        return;
    if (func_002533C0(p, 5) || func_002533C0(p, 6) || func_002533C0(p, 0x23) || func_002533C0(p, 7))
        return;
    if (t->p258 && func_00255D78(p, t->p258, D_00475440))
        return;
    x = func_002579A0(p, t);
    if (!x)
        return;
    switch (func_00257CB0(x)) {
    case 0:
        break;
    case 1:
        func_00238610(p->a29C, 0x13, t);
        break;
    }
}
