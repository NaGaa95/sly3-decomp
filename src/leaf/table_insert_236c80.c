// SLY3_CFLAGS: -Os -G0
// Insert an entry into the open-addressed pointer table: hash the entry's first word modulo 16381 and probe forward
// (wrapping) until a free slot is found. The table pointer is reloaded for every probe, the first probe enters at the test.
extern int **D_00474FC0;
void func_00236C80(int *entry)
{
    int index = *entry % 0x3FFD;
    int **slot = (int **)(((unsigned)index << 2) + (unsigned)D_00474FC0);
    goto test;
    do {
        index = (index + 1) % 0x3FFD;
        slot = (int **)(((unsigned)index << 2) + (unsigned)D_00474FC0);
test:   ;
    } while (*slot);
    *slot = entry;
}
