// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct B { char pad[0xA0]; int n; };
struct A { char pad[0x24]; struct B *pb; };
qword func_0028E910(int a, int n, qword q);
void func_002425D0(struct A *p, int a, int b, qword q);
void func_00242668(struct A *p, int a, int b, qword q)
{
    func_002425D0(p, a, b, func_0028E910(0, p->pb->n, q));
}
