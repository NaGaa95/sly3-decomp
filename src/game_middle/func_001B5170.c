// SLY3_CFLAGS: -Os -G0
// Walks the queued candidate entries (sorted by time, each with a target object) while their time has not passed the
// global limit, classifies the first target that matches one of the known kinds, and starts it with func_001B40F0.
// Returns 1 when something was started, 0 otherwise.
typedef int qword __attribute__((mode(TI)));
struct VirtualEntry { short adjustment; short reserved; qword *(*call)(void *); };
struct Owner { unsigned char opaque0[12]; struct VirtualEntry *vtable; };
struct Self { struct Owner *owner; };
struct Target { unsigned char pad0[0x11C]; int kind; };
struct Entry { struct Target *target; int param; float time; unsigned char pad0C[0x30 - 0x0C]; };
struct Queue { unsigned char pad0[0x4E78]; int count; int pad4E7C; struct Entry entries[1]; };
extern struct Queue D_00475480;
extern float D_00345700;
extern struct Owner *D_00370AC0;
int func_0013B500(void *object, int id);
qword func_00250600(struct Owner *owner);
int func_0027F310(void *object, qword position, qword anchor);
void func_001B40F0(void *self, int kind, void *target, int param);
int func_001B5170(struct Self *self)
{
    int count = D_00475480.count;
    int i;
    struct Target *target;
    int kind;
    struct Entry *entry;
    for (i = 0; i < count && !((entry = &D_00475480.entries[i])->time > D_00345700); i++) {
        target = entry->target;
        kind = -1;
        if (func_0013B500(target, 0x26) || func_0013B500(target, 0xA)) {
            kind = 5;
            if (self->owner == D_00370AC0)
                kind = 6;
        } else if (func_0013B500(target, 0x19)) {
            struct VirtualEntry *method = &self->owner->vtable[36];
            qword *matrix = method->call((char *)self->owner + method->adjustment);
            qword position = matrix[3];
            if (func_0027F310(target, position, func_00250600(self->owner)))
                kind = 8;
        } else if (func_0013B500(target, 0xB)) {
            kind = 0;
        } else if (func_0013B500(target, 0x20)) {
            kind = 0;
        } else if (func_0013B500(target, 0x24)) {
            kind = entry->target->kind;
        } else if (func_0013B500(target, 0x21)) {
            kind = 7;
        } else if (func_0013B500(target, 0x33)) {
            kind = 14;
        }
        if (kind != -1) {
            func_001B40F0(self, kind, target, entry->param);
            return 1;
        }
    }
    return 0;
}
