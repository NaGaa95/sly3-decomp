// Original USA entry 0x171808; complete ordinary C body.
// The signed count is reread after each helper call; index advances first.
// GCC2.95 zero-length tail array expresses the unknown original capacity.
// SLY3_CFLAGS: -Os -G0
struct Holder {
    char pad[420];
    int count;
    void *entries[0];
};
void func_00171090(void *);
void func_00171808(struct Holder *p) {
    int i=0;
    while(i<p->count)func_00171090(p->entries[i++]);
}
