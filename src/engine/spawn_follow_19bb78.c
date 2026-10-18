// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct FollowEntry {
    short delta, padding;
    union {
        void (*call)(void *);
        char *(*record)(void *);
        Qword (*vector)(void *);
    } method;
};
struct FollowSelf {
    unsigned char prefix[0xC];
    struct FollowEntry *table;
    unsigned char opaque10[0x180];
    void *source190;
    unsigned char opaque194[4];
    void *handle198;
};
void func_00240CB0(void *owner, int first, void *target, int flags, void *source, int second, Qword position, Qword facing, void **output);
void func_00179E10(void *handle);
void func_0019BB78(struct FollowSelf *self, void *target)
{
    if(target && self->source190) {
        char *record = self->table[36].method.record((char *)self + self->table[36].delta);
        Qword position = *(Qword *)(record + 0x30);
        Qword facing = self->table[38].method.vector((char *)self + self->table[38].delta);
        func_00240CB0(self, 0, target, 0x100, self->source190, 0, position, facing, 0);
    }
    if(self->handle198) func_00179E10(self->handle198);
    self->table[93].method.call((char *)self + self->table[93].delta);
}
