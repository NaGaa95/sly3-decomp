// SLY3_CFLAGS: -Os -G0 -ffast-math
// Refresh the entries of the 13-slot option menu from the selected object (key table D_00345F58; -1 = unused slot),
// then rebuild the menu list and flag the caller (same family as func_001D4C48).
struct VEntry { short d; short pad; int (*pfn)(void *, int); };
struct Object { char pad00[0xC]; struct VEntry *vt; };
struct Menu { char pad00[0x18]; int selected; char pad1C[0x30 - 0x1C]; int x30; };
struct Caller { char pad00[0x1C]; int x1C; };
extern struct Menu D_0046F550;
extern char D_00475480[], D_0036C700[];
extern int D_00345F58[];
extern char D_00345F30[];
void func_001854C8(void *p, int n, int m);
struct Object *func_001F4AD0(void *table, int id);
void func_00262B00(int a, int key, int enabled);
void func_001D3960(struct Menu *g, int n, int a, int b, void *list);
void func_001D5058(struct Caller *caller)
{
    struct Object *obj;
    int i;
    func_001854C8(D_0036C700, 0x3B, 0);
    if (D_0046F550.selected == -1)
        obj = 0;
    else
        obj = func_001F4AD0(D_00475480, D_0046F550.selected);
    if (obj) {
        for (i = 0; i < 13; i++) {
            int key = D_00345F58[i];
            if (key != -1) {
                int result = obj->vt[91].pfn((char *)obj + obj->vt[91].d, i);
                func_00262B00(D_0046F550.x30, key, result == -1);
            }
        }
        func_001D3960(&D_0046F550, 0, 0, 0, D_00345F30);
        if (caller)
            caller->x1C |= 2;
    }
}
