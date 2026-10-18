// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword rows[4]; } Mat4;
struct VirtualEntry {
    short adjustment, reserved;
    void (*method)(void *);
};
struct RestoreObject {
    unsigned char prefix[0xC];
    struct VirtualEntry *table;
    unsigned char opaque10[0x40];
    Mat4 matrix50;
    unsigned char opaque90[0x2A4 - 0x90];
    int flag2A4;
    unsigned char opaque2A8[8];
    Mat4 saved2B0;
    float height2F0;
};
void func_001FC8F8(void *receiver, void *owner);
void func_00290078(void *object);
void func_00167960(void *object, float height);
void func_00165AB0(struct RestoreObject *self, void *owner)
{
    func_001FC8F8(self, owner);
    self->matrix50 = self->saved2B0;
    func_00290078(self);
    func_00167960(self, self->height2F0);
    if(!self->flag2A4) self->table[56].method((char *)self + self->table[56].adjustment);
}
