// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct R { char pad[0x14]; int n14; };
struct P { char pad[0x20]; void *p20; void *p24; };
struct R *func_00242500(struct P *, int, int, int);
void func_0012F4F8(struct R *, qword);
void func_00130078(void *, void *, int, int, int, qword);
void func_002425D0(struct P *p, int n, int m, qword q)
{
    struct R *r = func_00242500(p, 1, n, m);
    if (r) {
        r->n14 = n;
        func_0012F4F8(r, q);
    } else if (n != -1) {
        func_00130078(p->p20, p->p24, m, n, 2, q);
    }
}
