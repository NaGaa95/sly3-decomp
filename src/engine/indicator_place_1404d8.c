// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct PlaceEntry {
    short delta, padding;
    union {
        char *(*record)(void *);
        void (*place)(void *, Qword);
    } method;
};
struct PlaceTarget {
    unsigned char prefix[0xC];
    struct PlaceEntry *table;
};
struct PlaceSelf {
    unsigned char prefix[0x19B8];
    struct PlaceTarget *indicator;
    void *prototype;
};
int func_00287890(void *first, Qword point, Qword *output);
struct PlaceTarget *func_001FBE30(void *prototype, int flag);
void func_001C8FB0(void *object, void *source);
void func_00287080(void *object, void *first, void *second, Qword position, Qword extra);
void func_00286D68(void *object, void *owner);
int func_001404D8(struct PlaceSelf *self, struct PlaceTarget *target, void *first, void *second, Qword extra)
{
    Qword placement;
    if(!func_00287890(0, *(Qword *)(target->table[36].method.record((char *)target + target->table[36].delta) + 0x30), &placement)) return 0;
    self->indicator = func_001FBE30(self->prototype, 0);
    if(!self->indicator) return 0;
    func_001C8FB0(self->indicator, target);
    self->indicator->table[34].method.place((char *)self->indicator + self->indicator->table[34].delta, placement);
    func_00287080(self->indicator, first, second, *(Qword *)(target->table[36].method.record((char *)target + target->table[36].delta) + 0x30), extra);
    func_00286D68(self->indicator, self);
    return 1;
}
