// SLY3_CFLAGS: -Os -G0 -ffast-math
// qsort comparator of func_001B67C0: orders entries by the float at +8.
struct TimedEntry {
    char pad00[8];
    float time;
};

int func_001B6798(const struct TimedEntry *a, const struct TimedEntry *b)
{
    if (a->time < b->time)
        return -1;
    return 1;
}
