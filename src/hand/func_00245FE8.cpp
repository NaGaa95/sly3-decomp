// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct A; struct B;
struct X {
    static void *operator new(unsigned int cb);
    X(A *pa, B *pb);
    char pad[0x3C0];
};
extern "C" extern "C" X *func_00245FE8(A *pa, B *pb)
{
    X *px;
    if (pa)
        px = new X(pa, pb);
    else
        px = 0;
    return px;
}
