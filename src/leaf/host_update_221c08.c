// Per-frame update of the host panel: after the base update, map pad buttons to actions (0x10 opens the pick menu, 0x800 confirms or closes the save panel, 0x100 steps the selection) and fill the pick-menu choices from the id list.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct PickChoice {
    int label;
    void (*select)(void *);
    int id;
    int word0C, word10, word14, word18, word1C;
};
struct Host {
    unsigned char pad00[0x18];
    int menuSelection;
    void *controller;
    unsigned char pad20[0x34 - 0x20];
    int active;
    unsigned char pad38[0x50 - 0x38];
    int closing;
};
struct Mode { unsigned char pad[8]; int value; };
struct SaveSelectionView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
    void *pendingBlock;
};
struct Panel { unsigned char pad[0x58]; int busy; };
struct IdList {
    int count;
    int *ids;
};
extern struct PickChoice D_0046FD48[];
extern int D_0046FD44;
extern int D_003493A8[];
extern int D_003493E8[];
extern unsigned char D_00475480[];
extern unsigned char D_0046F550[];
extern unsigned char D_0036F864[];
extern struct Panel D_003751D0;
extern unsigned char D_00375290[];
void func_0021EBE0(struct Host *host);
int func_0011C330(void);
int func_001A7A80(void *controller, int button, float hold);
int func_001A7AE0(void *controller, int button, int mode);
void func_00221FA8(struct Host *host);
int func_00221AC0(struct Host *host);
void func_00210EC0(void *object);
void func_001D0D30(void *panel, int mode);
void func_0018AB08(void *block);
void func_001D4BF8(int selection);
void func_00221EC0(struct Host *host);
void *func_0017E1B8(void *game, int flags, int key, void *owner);
void func_0011C2E0(int *count, int **ids);
void *func_00292034(void *destination, int value, unsigned int count);
void func_00221BC0(void *entry);
void func_001D2D90(void *menu, int selection);
void func_001D3960(void *menu, int count, struct PickChoice *choices, int active, int title);

void func_00221C08(struct Host *host)
{
    func_0021EBE0(host);
    if (!host->active) return;
    if (host->closing) return;
    if (((struct Mode *)D_00375290)->value == 5) return;
    if (func_0011C330() >= 2 && host->controller && func_001A7A80(host->controller, 0x10, 0.0f))
        func_00221FA8(host);
    if (func_00221AC0(host)) return;
    if (!host->controller) return;
    D_0046FD44 = 1;
    func_00210EC0(D_0036F864);
    func_00210EC0(D_0036F864 + 0x11C0);
    if (func_001A7A80(host->controller, 0x800, 0.0f)) {
        struct SaveSelectionView *view = (struct SaveSelectionView *)D_00375290;
        view->selectedBlock = view->pendingBlock;
        if (view->pendingBlock) {
            func_001D0D30(&D_003751D0, 1);
            func_0018AB08(view->selectedBlock);
            return;
        }
        if (!D_003751D0.busy && func_0011C330() >= 2) {
            host->closing = 1;
            func_001D0D30(&D_003751D0, 1);
            return;
        }
        func_00221EC0(host);
        return;
    }
    if (func_001A7AE0(host->controller, 0x100, 8)) {
        func_001D4BF8(host->menuSelection);
        return;
    }
    if (func_0011C330() < 2) return;
    if (func_001A7A80(host->controller, 0x10, 0.0f)) {
        struct IdList list;
        void *object = func_0017E1B8(D_00475480, 5, 0x6A7, 0);
        int i;
        if (!object) return;
        func_0011C2E0(&list.count, &list.ids);
        for (i = 0; i < list.count; i++) {
            int id = list.ids[i];
            struct PickChoice *choice = &D_0046FD48[i];
            func_00292034(choice, 0, 0x20);
            choice->label = D_003493A8[id];
            choice->select = func_00221BC0;
            choice->id = id;
        }
        func_001D2D90(D_0046F550, host->menuSelection);
        func_001D3960(D_0046F550, list.count, D_0046FD48, (int)object, (int)D_003493E8);
    }
}
