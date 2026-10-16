// SLY3_CFLAGS: -Os -G0
struct CatalogChoice;
struct CatalogEntry {
    int label;
    unsigned char opaque04[0x54 - 4];
};
struct CatalogResource {
    unsigned char opaque00[0x40];
    int count;
    struct CatalogEntry *entries;
};
struct CatalogChoice {
    int label;
    void (*select)(struct CatalogChoice *);
    int index;
    struct CatalogResource *catalog;
    int word10, word14, word18;
    unsigned int flags;
};
struct CatalogPanel {
    unsigned char opaque00[0x18];
    unsigned int flags;
};
struct CatalogMenu {
    unsigned char opaque00[0x1C];
    struct CatalogPanel *panel;
    unsigned char opaque20[0x34 - 0x20];
    int active;
    int depth;
};
extern struct CatalogMenu D_0046F550;
extern unsigned char D_00475480[], D_00345920[];
extern struct CatalogChoice D_00388D28[];
int func_0025AE28(void *game);
void *func_0017E1B8(void *game, int flags, int key, void *owner);
void func_001D4DE8(struct CatalogChoice *choice);
void func_001D3A90(void *menu);
void func_001D3960(void *menu, int count, struct CatalogChoice *choices,
                   int active, int title);

void func_001D4E10(struct CatalogChoice *request)
{
    struct CatalogResource *catalog;
    struct CatalogChoice *output;
    int i;
    if (!D_0046F550.active || func_0025AE28(D_00475480)) return;
    catalog = 0;
    if (D_0046F550.panel && (D_0046F550.panel->flags & 1))
        catalog = func_0017E1B8(D_00475480, 5, 0x73B, 0);
    if (!catalog)
        catalog = func_0017E1B8(D_00475480, 5, 0x73A, 0);
    if (!catalog) return;
    output = D_00388D28;
    for (i = 0; i < catalog->count; ++i) {
        struct CatalogEntry *entry = &catalog->entries[i];
        int label = entry->label;
        output->index = i;
        output->select = func_001D4DE8;
        output->label = label;
        output->catalog = catalog;
        ++output;
    }
    if (output != D_00388D28) {
        if (D_0046F550.depth > 0) {
            func_001D3A90(&D_0046F550);
            --D_0046F550.depth;
        }
        func_001D3960(&D_0046F550, output - D_00388D28,
                      D_00388D28, D_0046F550.active, (int)D_00345920);
        if (request) request->flags |= 2;
    }
}
