// SLY3_CFLAGS: -Os -G0
struct MenuRecord {
    int word0;
    void *entries;
    int opaque[5];
};

struct MenuSelection {
    char opaque[0x38];
    int count;
    struct MenuRecord records[0];
};

extern char D_00345990[], D_003459F0[], D_00345A50[], D_00345AB0[];
int func_0021DD30(void *menu);

int func_001D45B0(struct MenuSelection *menu)
{
    int count;
    void *entries;

    if (!func_0021DD30(menu))
        return -1;
    count = menu->count;
    if (count <= 0)
        return -1;
    entries = menu->records[count - 1].entries;
    if (entries == D_00345990)
        return 0x2A;
    if (entries == D_003459F0)
        return 0x2B;
    if (entries != D_00345A50)
        return entries != D_00345AB0 ? -1 : 0x57;
    return 0x25;
}
