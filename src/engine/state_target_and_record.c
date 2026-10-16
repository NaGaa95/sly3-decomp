// SLY3_CFLAGS: -Os -G0
struct PairStateFields {
    char prefix[0x11D0];
    void *target;
    int value;
    char unaccessed11D8[0x1218-0x11D8];
    int dirty;
    float amount;
};
extern float D_003205AC;
void func_00155308(void *receiver);
void func_00155270(struct PairStateFields *p, int value, void *target)
{
    if (target != p->target || value != p->value) {
        p->value = value;
        p->target = target;
        if (target && p->amount != D_003205AC) {
            p->dirty = 1;
            func_00155308(p);
        }
    }
}

struct Object;
struct Object *func_00169C90(struct Object *receiver, void *owner, int order);
extern unsigned char D_00355D40[];
struct RuntimeRecord {
    void *owner;
    int order;
    int kind;
    char unaccessedC[0x1C-0xC];
    void *table;
    void *object;
    char unaccessed24[0x3C-0x24];
    float value;
    char unaccessed40[8];
    unsigned int word48, word4C;
};
void *func_00169F60(struct RuntimeRecord *p, void *owner, int order, void *object)
{
    func_00169C90((struct Object *)p, owner, order);
    p->table = D_00355D40;
    p->object = object;
    p->kind = 3;
    p->value = 7.0f;
    p->word48 = 0;
    p->word4C = 0;
    return p;
}
