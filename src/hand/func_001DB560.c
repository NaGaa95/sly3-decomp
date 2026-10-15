// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct M {
    int a, b;
    unsigned char *n8;
    unsigned int nC;
};
struct S {
    char pad[0x160];
    char x160[0x10];
    unsigned int c170;
};
int func_0014F1C8(void *p, int cb, unsigned char *pb);
int func_001DB560(void *a, struct M *pm, struct S *p) {
    if (p->c170 < pm->nC) return 0;
    func_0014F1C8(p->x160, pm->nC, pm->n8);
    return 1;
}
