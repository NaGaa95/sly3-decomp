// Original USA entry 0x15c688; ordinary C reconstruction.
// Receiver A0 and all three word-sized record values A1/A2/A3 are explicit. Signed countDC is reloaded before each12-byte-record field write, preserving original alias-sensitive ordering, then incremented. No additional incoming register is consumed.
// SLY3_CFLAGS: -Os -G0
struct Entry  {
    void *a,*b,*c;
};
struct Object  {
    char pad[0xDC];
    int count;
    struct Entry entries[1];
};
void func_0015C688(struct Object *p,void *a,void *b,void *c)  {
    p->entries[p->count].a=a;
    p->entries[p->count].b=b;
    p->entries[p->count].c=c;
    ++p->count;
}
