// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
extern "C" DLI *D_0036AE94;
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list)
        : pdl(list), ppv((void **)list), ibDle(list->ibDle),
          pdliNext(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~DLI()
    {
        D_0036AE94 = pdliNext;
    }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};
struct Entry { unsigned char prefix[0x1B8]; int kind; unsigned char gap1BC[0x518 - 0x1BC]; int word518; };
struct Selection { unsigned char prefix[0x40]; int word40; Entry *entries[5]; int count; };
extern "C" {
extern DL D_00479BEC;
void func_002171E8(void *entry, int mode);
void func_002159D8(void *entry, int mode);
void func_00219A18(void *selection, int mode);
}
extern "C" void func_0021A1C8(Selection *selection, int mode)
{
    if (selection->count < 2) {
        selection->count = 0;
        return;
    }
    DLI iterator(&D_00479BEC);
    Entry *entry;
    while ((entry = (Entry *)iterator.Next()) != 0) {
        int found = 0;
        for (int i = 0; i < selection->count; i++) {
            if (entry == selection->entries[i]) {
                found = 1;
                entry->word518 = 0;
                if (entry->kind == 2)
                    func_002171E8(entry, 2);
                func_002159D8(entry, 4);
                break;
            }
        }
        if (!found)
            CallScene((SCENE_OBJECT *)entry, 9);
    }
    selection->word40 = mode;
    func_00219A18(selection, 1);
}
