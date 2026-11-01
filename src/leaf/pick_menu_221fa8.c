// Build the pick menu: find the entry matching the current selection id, fill the choice table starting from it (wrapping around) and open the menu on the found object.
// SLY3_CFLAGS: -Os -G0
struct PickChoice {
    int label;
    void (*select)(void *);
    int id;
    int word0C, word10, word14, word18, word1C;
};
struct IdList {
    int count;
    int *ids;
};
extern struct PickChoice D_0046FD48[];
extern int D_003493A8[];
extern int D_003493E8[];
extern unsigned char D_00475480[];
extern unsigned char D_0046F550[];
extern int D_0036B120;
void *func_0017E1B8(void *game, int flags, int key, void *owner);
void func_0011C2E0(int *count, int **ids);
void *func_00292034(void *destination, int value, unsigned int count);
void func_00221BC0(void *entry);
void func_001D2D90(void *menu, int selection);
void func_001D3960(void *menu, int count, struct PickChoice *choices, int active, int title);

void func_00221FA8(void)
{
    struct IdList list;
    int start;
    int i;
    void *object = func_0017E1B8(D_00475480, 5, 0x6A7, 0);
    if (!object) return;
    func_0011C2E0(&list.count, &list.ids);
    start = 0;
    {
        int j;
        for (j = 0; j < list.count; j++) {
            if (list.ids[j] == D_0036B120) {
                start = j;
                break;
            }
        }
    }
    for (i = 0; i < list.count; i++) {
        struct PickChoice *choice = &D_0046FD48[i];
        int id = list.ids[(i + start) % list.count];
        func_00292034(choice, 0, 0x20);
        choice->label = D_003493A8[id];
        choice->select = func_00221BC0;
        choice->id = id;
    }
    func_001D2D90(D_0046F550, 0);
    func_001D3960(D_0046F550, list.count, D_0046FD48, (int)object, (int)D_003493E8);
}
