// Sort comparator on the float at +4 (ascending).
// SLY3_CFLAGS: -O2 -G0 -ffast-math
struct SortKey { float first; float key; };
int func_002047A8(const struct SortKey *a, const struct SortKey *b)
{
    return a->key < b->key ? -1 : 1;
}
