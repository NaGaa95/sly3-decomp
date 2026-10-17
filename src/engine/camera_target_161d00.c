// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct TargetEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct TargetRecord { unsigned char prefix[0x30]; int kind; unsigned char gap34[0x40 - 0x34]; int mode; };
struct TargetSelf {
    unsigned char prefix[0xC]; struct TargetEntry *table;
    unsigned char gap10[0x218 - 0x10]; int flag;
    unsigned char gap21C[0x248 - 0x21C]; float heightA;
    unsigned char gap24C[0x268 - 0x24C]; float heightB;
    unsigned char gap26C[0x29C - 0x26C]; unsigned char list[1];
};
struct TargetOut {
    union { Qword quad; float lane[4]; } position; unsigned char gap10[0x54 - 0x10]; float weight;
    unsigned char gap58[0x6C - 0x58]; unsigned int flags;
};
void func_00257478(void *self, void *out);
struct TargetRecord *func_002387A8(void *list, int key);
void func_00161D00(struct TargetSelf *self, struct TargetOut *out)
{
    struct TargetRecord *record;
    func_00257478(self, out);
    out->weight = 100.0f;
    out->position.quad = *(Qword *)(self->table[36].method((unsigned char *)self + self->table[36].delta) + 0x30);
    if(self->flag) {
        out->position.lane[2] = self->heightA + 125.0f;
    } else {
        out->position.lane[2] += self->heightB + 125.0f;
        out->flags |= 4;
    }
    record = func_002387A8(self->list, 0xE9);
    if(record) {
        if(record->mode == 1) out->position.lane[2] += 50.0f;
        if(record->kind == 0xE) out->weight = 0.0f;
    }
}
