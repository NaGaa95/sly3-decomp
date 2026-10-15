// Original USA entry 0x1f9030; ordinary C reconstruction.
// Receiver A0 loads its array1B4; the explicit word-sized value A1 is appended only when unsigned count1C<3. The complete44-byte entry returns before the separately preserved getter.
// SLY3_CFLAGS: -Os -G0
struct Array  {
    char pad[0x1C];
    unsigned int count;
    void *items[3];
};
struct Object  {
    char pad[0x1B4];
    struct Array *array;
};
void func_001F9030(struct Object *p,void *value)  {
    struct Array *a=p->array;
    if(a->count<3)a->items[a->count++]=value;
}
