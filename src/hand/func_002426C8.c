// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword a[3]; };
struct O { char pad[0xA0]; int nA0; };
struct P { char pad[0x24]; struct O *po; };
void func_0028EA00(struct M3 *, int, int);
qword func_0011D3C0(struct M3 *);
void func_002425D0(struct P *, int, int, qword);
void func_002426C8(struct P *p, int a, int b)
{
    struct M3 c, t;
    func_0028EA00(&t, 0, p->po->nA0);
    c = t;
    func_002425D0(p, a, b, func_0011D3C0(&c));
}
