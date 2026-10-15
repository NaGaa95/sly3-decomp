// SLY3_CFLAGS: -Os -G0
struct MenuStatusRecord {
    unsigned char opaque00[0x48];
    int kind;
    float changedAt;
    unsigned char opaque50[4];
    int category;
};
struct MenuStatusView {
    unsigned char opaque00[0x34];
    struct MenuStatusRecord *record;
};
extern float D_0036BBD8;
extern unsigned char D_00388BF0[];
void func_0021EBE0(void *menu);
int func_001CEFB8(void *worker);
void func_001D2100(void *menu);

int func_001D2138(void *receiver)
{
    struct MenuStatusView *menu = receiver;
    struct MenuStatusRecord *record = menu->record;
    if (!record)
        return 0;
    if (record->kind < 2 && record->category < 2)
        return 0;
    return 1;
}

void func_001D2178(void *receiver)
{
    struct MenuStatusView *menu = receiver;
    struct MenuStatusRecord *record;
    func_0021EBE0(receiver);
    record = menu->record;
    if (record) {
        int kind = record->kind;
        if (kind == 2 && record->category == kind &&
            D_0036BBD8 - record->changedAt > 1.0f &&
            !func_001CEFB8(D_00388BF0))
            func_001D2100(receiver);
    }
}
