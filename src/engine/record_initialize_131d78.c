// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct InitEntry { short delta, padding; char *(*fn)(void *); };
struct InitHolder { unsigned char prefix[0xC]; struct InitEntry *table; };
struct InitSelf {
    unsigned char prefix[0x10]; struct InitHolder *holder;
    unsigned char gap14[0x3C - 0x14]; int state;
    unsigned char gap40[0xC8 - 0x40]; int wordC8; int wordCC; int wordD0;
    unsigned char gapD4[0xD8 - 0xD4]; int wordD8;
    unsigned char gapDC[0xF0 - 0xDC]; float fF0; float fF4; float fF8; float fFC;
    unsigned char gap100[0x110 - 0x100]; Qword vector;
};
void func_00131568(void *self);
void func_00131D78(struct InitSelf *self)
{
    struct InitHolder *holder;
    char *record;
    func_00131568(self);
    self->state = 0x15;
    self->wordD0 = -1;
    self->wordD8 = -1;
    self->wordCC = -1;
    self->fF0 = 1.0f;
    holder = self->holder;
    record = holder->table[36].fn((char *)holder + holder->table[36].delta);
    self->vector = *(Qword *)(record + 0x30);
    self->fF8 = 800.0f;
    self->fFC = 0.75f;
    self->fF4 = 1.0f;
    self->wordC8 = 1;
}
