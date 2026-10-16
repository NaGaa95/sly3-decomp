// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Object;
struct Object *func_00169C90(struct Object *receiver, void *owner, int order);
extern unsigned char D_003530F8[];
extern qword D_00342D60, D_00317560;
struct PackedRecord {
    void *owner;
    int order, kind;
    char unaccessedC[0x1C-0xC];
    void *table;
    void *subject;
    char unaccessed24[0x30-0x24];
    qword value30, value40;
};
void *func_001473A0(struct PackedRecord *p, void *owner, int order, void *subject)
{
    func_00169C90((struct Object *)p, owner, order);
    p->kind = 9;
    p->table = D_003530F8;
    p->subject = subject;
    p->value30 = D_00342D60;
    p->value40 = D_00317560;
    return p;
}
extern unsigned char D_0036BC10[];
int func_00169150(void *selection, int identity);
int func_00151D10(int count, const int *identities)
{
    int i;
    if (!count)
        return 1;
    for (i = 0; i < count; ++i) {
        if (func_00169150(D_0036BC10, identities[i]))
            return 1;
    }
    return 0;
}
