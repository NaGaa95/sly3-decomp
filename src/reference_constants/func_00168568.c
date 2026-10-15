// Original USA entry 0x168568; complete ordinary C body.
// The signed count is reread after each helper call; index advances first.
// GCC2.95 zero-length tail array expresses the unknown original capacity.
// SLY3_CFLAGS: -Os -G0
struct Holder {
    char pad[16056];
    int count;
    void *entries[0];
};
void func_001685C8(void *);
void func_00168568(struct Holder *p) {
    int i=0;
    while(i<p->count)func_001685C8(p->entries[i++]);
}
