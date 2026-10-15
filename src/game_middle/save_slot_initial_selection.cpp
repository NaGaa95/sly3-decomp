// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class SlotReference {
public:
    CRef value;
    SlotReference(const SlotReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~SlotReference() { Drop(); }
};
typedef char SlotReferenceSizeIsEight[(sizeof(SlotReference) == 8) ? 1 : -1];
struct SaveBlock { unsigned char bytes[0x6864]; };
struct SaveData {
    unsigned char opaque[0x24];
    SaveBlock blocks[3];
    SaveBlock *selected;
};
struct Menu {
    unsigned char opaque[0x38];
    int count;
};
struct MenuRecord {
    unsigned char opaque[0x14];
    int selection;
    int word18;
};
struct KEY;
extern "C" {
extern unsigned char D_003751D0[];
extern SaveData D_00375290;
extern Menu D_0046F550;
extern MenuRecord D_0046F570[];
extern KEY *D_004794EC;
void func_001D0D30(void *menu, int mode);
int func_001D45B0(void *menu);
SlotReference QuerySaveSlot(KEY *key, unsigned char *buffer)
    __asm__("func_002BC010");
}
static inline float SlotPresent(SaveBlock *block)
{
    return QuerySaveSlot(D_004794EC, block->bytes).value.payload.real;
}
extern "C" void func_001D17F0(void)
{
    float present[3];
    MenuRecord *record;
    int i;

    func_001D0D30(D_003751D0, 1);
    if (D_0046F550.count <= 0)
        return;
    record = &D_0046F570[D_0046F550.count];
    for (i = 0; i < 3; ++i)
        present[i] = SlotPresent(&D_00375290.blocks[i]);
    switch (func_001D45B0(&D_0046F550)) {
    case 0x2A:
        for (int j = 0; j < 3; ++j) {
            if (present[j] == 0.0f) {
                record->selection = j;
                break;
            }
        }
        break;
    case 0x2B:
        for (int j = 0; j < 3; ++j) {
            if (present[j] != 0.0f) {
                record->selection = j;
                break;
            }
        }
        break;
    case 0x25: {
        if (D_00375290.selected)
            record->selection = D_00375290.selected - D_00375290.blocks;
        break;
    }
    }
}
