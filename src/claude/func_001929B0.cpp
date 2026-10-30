// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ALLOCREQ { int cb; int nKind; };
class CBinaryInputStream {
public:
    unsigned char U8Read();
    unsigned short U16Read();
    int S32Read();
    void Skip(int cb);
};
struct Entry { unsigned short a, b; unsigned char c; unsigned char pad; };
struct Item { int id; int count; Entry *entries; };
struct Table { int count; Item *items; };
void *PvAllocSlot(ALLOCREQ *preq);
extern "C" {
extern unsigned char D_0036BC10[];
void *func_001D2670(ALLOCREQ *preq);
int func_00169150(void *registry, int id);
void func_00236830(unsigned short *p);
}
extern "C" Table *func_001929B0(void *unused, CBinaryInputStream *bis)
{
    Table *table = 0;
    int n = bis->U8Read();
    int i, j, k;
    for (i = 0; i < n; i++) {
        int id = bis->S32Read();
        int count = bis->U16Read();
        if (!func_00169150(D_0036BC10, id)) {
            for (j = 0; j < count; j++) {
                bis->U16Read();
                int cb = bis->U16Read();
                bis->Skip(cb * 5);
            }
            continue;
        }
        ALLOCREQ req;
        req.cb = sizeof(Table);
        req.nKind = 0x10;
        table = (Table *)func_001D2670(&req);
        table->count = count;
        req.cb = count * sizeof(Item);
        req.nKind = 0x10;
        table->items = (Item *)func_001D2670(&req);
        for (j = 0; j < count; j++) {
            Item *item = &table->items[j];
            item->id = bis->U16Read();
            item->count = bis->U16Read();
            req.cb = item->count * sizeof(Entry);
            req.nKind = 0x10;
            item->entries = (Entry *)PvAllocSlot(&req);
            for (k = 0; k < item->count; k++) {
                Entry *e = &item->entries[k];
                unsigned short *pb = &e->b;
                e->a = bis->U16Read();
                *pb = bis->U16Read();
                e->c = bis->U8Read();
                func_00236830(&e->a);
                func_00236830(pb);
            }
        }
    }
    return table;
}
