// SLY3_CFLAGS: -Os -G0
int func_0021F410(int identity);
struct PredicateFields {
    char unaccessed0[0xF4];
    int count;
    int *identities;
};
int func_00139928(struct PredicateFields *p)
{
    int i;
    if (!p->count)
        return 1;
    for (i = 0; i < p->count; ++i) {
        if (func_0021F410(p->identities[i]))
            return 1;
    }
    return 0;
}
