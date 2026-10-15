// Original USA entry 0x1e5ab0; ordinary C reconstruction.
// Receiver A0, 32-bit kind A1 and optional object pointer A2 are explicit. Signed count130<8 admits one complete8-byte record and increments count before stores. Only nonnull object triggers 241628(receiver, enabled1); its existing recovered definition consumes exactly those inputs.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    int kind;
    void *object;
};
struct Object  {
    char pad[0x130];
    int count;
    struct Record *records;
};
void func_00241628(void *,int);
void func_001E5AB0(struct Object *p,int kind,void *object)  {
    if(p->count<8) {
        struct Record *r=p->records+p->count++;
        r->kind=kind;
        r->object=object;
        if(object)func_00241628(p,1);
    }
}
