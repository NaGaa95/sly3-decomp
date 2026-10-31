// SLY3_CFLAGS: -Os -G0
// Object setup: base initializers, then fill the attached transform record (world matrix from the owner chain, optional
// extra vectors, flag bit 52 of the object flags).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct VirtualEntry { short delta; short pad; void *(*call)(void *); };
struct Record { M4 world; qword q40; qword q50; int flag60; };
struct Self {
    unsigned char pad00[0xC]; struct VirtualEntry *vtable; void *owner;
    unsigned char pad14[0x28 - 0x14]; unsigned long flags;
    unsigned char pad30[0x48 - 0x30]; int x48; int x4C;
    unsigned char pad50[0x120 - 0x50]; struct Record *record;
};
void func_001C7DC8(void *self);
void func_0028E768(void *self);
void func_0018DA48(void *list);
M4 func_001C9708(void *first, void *second, M4 *matrix);
qword func_0023D888(void *self);
qword func_0023D8E0(void *self);
static inline M4 *Matrix(struct Self *object)
{
    struct VirtualEntry *entry = &object->vtable[36];
    return (M4 *)entry->call((char *)object + entry->delta);
}
void func_0023C580(struct Self *self)
{
    struct Record *record;
    func_001C7DC8(self);
    func_0028E768(self);
    func_0018DA48((char *)self + 0x70);
    record = self->record;
    if (record) {
        record->world = func_001C9708(0, self->owner, Matrix(self));
        if (self->x48) {
            struct Record *r = self->record;
            r->q40 = func_0023D888(self);
        }
        if (self->x4C) {
            struct Record *r = self->record;
            r->q50 = func_0023D8E0(self);
        }
        {
            struct Record *r = self->record;
            r->flag60 = (int)(self->flags >> 52) & 1;
        }
    }
}
