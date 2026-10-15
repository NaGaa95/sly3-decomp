// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { unsigned int c; int a[0x100]; };
void func_00211120(struct S *p, int n) {
    if (p->c < 0x100) {
        p->a[p->c++] = n;
    }
}
