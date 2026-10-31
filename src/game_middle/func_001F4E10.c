// Store the second argument into the field at +0x10.
// SLY3_CFLAGS: -O2 -G0 -ffast-math

struct Holder {
    char pad[0x10];
    void *link;
};

void func_001F4E10(struct Holder *self, void *link)
{
    self->link = link;
}
