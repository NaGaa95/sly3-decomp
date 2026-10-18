// SLY3_CFLAGS: -Os -G0
struct ResetEntry { short delta, padding; union { void (*method)(void *); void (*set)(void *, int); } call; };
struct ResetPart { int first, second, third; };
struct ResetObject {
    unsigned char prefix[0xC]; struct ResetEntry *table;
    unsigned char gap10[0x940 - 0x10]; unsigned char block940[0xE40 - 0x940]; unsigned char blockE40[0x1250 - 0xE40];
    struct ResetPart parts[3];
    int word1274;
};
void func_0024DB18(void *object);
void func_001C20A8(void *block);
void func_00155ED8(void *object, int flag);
void func_002093E8(void *block);
void func_00153EA0(void *object, int flag);
void func_00154350(void *object, void *part, int flag);
void func_00152828(struct ResetObject *self)
{
    int i;
    func_0024DB18(self);
    self->table[102].call.method((char *)self + self->table[102].delta);
    func_001C20A8(self->blockE40);
    func_00155ED8(self, 0);
    func_002093E8(self->block940);
    func_00153EA0(self, 0);
    for(i = 0; i < 3; i++) func_00154350(self, &self->parts[i], 0);
    self->word1274 = 0;
    self->table[99].call.set((char *)self + self->table[99].delta, -1);
}
