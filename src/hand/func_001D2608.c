// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct MSG { int cb; int nKind; };
void *func_001D25B0(struct MSG *pm);
void func_001D2898(void *, void *, int);
void *func_001D2608(struct MSG *pm, void *pvSrc)
{
    struct MSG m = *pm;
    void *p = func_001D25B0(&m);
    if (p) func_001D2898(p, pvSrc, pm->cb);
    return p;
}
