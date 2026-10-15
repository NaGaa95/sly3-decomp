// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x150]; unsigned int c; int a[7]; };
void func_002237F8(struct S *p, int n) {
    if (p->c < 7) {
        p->a[p->c++] = n;
    }
}
