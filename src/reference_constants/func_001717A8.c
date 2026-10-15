// Original USA entry 0x1717a8; complete ordinary C body.
// The signed count is reread after each helper call; index advances first.
// GCC2.95 zero-length tail array expresses the unknown original capacity.
// SLY3_CFLAGS: -Os -G0
struct Holder {
    char pad[420];
    int count;
    void *entries[0];
};
void func_00171050(void *);
void func_001717A8(struct Holder *p) {
    int i=0;
    while(i<p->count)func_00171050(p->entries[i++]);
}
