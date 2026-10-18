// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct InitEntry { short delta, padding; qword *(*fn)(void *); };

struct InitSelf { unsigned char prefix[0xC]; struct InitEntry *table; unsigned char gap10[0x1E0 - 0x10]; qword vector; };
void func_0023C660(void *self);
qword func_0011D3C0(qword *source);
void func_00141580(void *self);
void func_001451C8(void *self);
void func_00145AC0(void *self);
void func_00145E40(void *self);
void func_00145ED8(void *self);
void func_00146058(void *self);
void func_00146360(void *self);
void func_00141500(struct InitSelf *self)
{
    func_0023C660(self);
    self->vector = func_0011D3C0(self->table[36].fn((char *)self + self->table[36].delta));
    func_00141580(self);
    func_001451C8(self);
    func_00145AC0(self);
    func_00145E40(self);
    func_00145ED8(self);
    func_00146058(self);
    func_00146360(self);
}
