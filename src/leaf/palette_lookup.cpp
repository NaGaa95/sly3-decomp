// Reference: Sly 2 func_001EC918; actual Sly 3 pointer fields and cleanup.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct PaletteLookupNode {
    char reserved0[0x14];
    int id;
    char reserved18[0x34 - 0x18];
    void *child;
    char reserved38[0x44 - 0x38];
    PaletteLookupNode *next;
};
extern "C" PaletteLookupNode *D_00479DA4;

class PaletteSearchToken {
public:
    ~PaletteSearchToken();
};

extern "C" PaletteLookupNode *func_00235F80(int id)
{
    if (id == -1)
        return 0;
    PaletteSearchToken token;
    for (PaletteLookupNode *node = D_00479DA4; node; node = node->next) {
        if (node->child)
            break;
        if (node->id == id)
            return node;
    }
    return 0;
}
