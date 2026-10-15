// Original USA entry 0x139538; ordinary C reconstruction.
// Receiver A0 and optional item A1 are explicit. Unsigned count130<4 admits actual item.object18 into receiver134[count], increments count and calls13CD10(global475480,receiver). Complete13CD10 consumes those two pointers and creates its own remaining list inputs.
// SLY3_CFLAGS: -Os -G0
struct Item  {
    char pad[0x18];
    void *object;
};
struct Holder  {
    char pad[0x130];
    unsigned int count;
    void *objects[4];
};
extern char D_00475480[];
void func_0013CD10(void *,void *);
void func_00139538(struct Holder *p,struct Item *item)  {
    if(p->count<4 && item) {
        p->objects[p->count++]=item->object;
        func_0013CD10(D_00475480,p);
    }
}
