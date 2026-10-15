// SLY3_CFLAGS: -Os -G0
#include "selection_types.h"

int func_0021F350(int id);
int func_0021F410(int id);
void func_002200B8(Selection *, int);

void func_002201D8(Selection *selection)
{
    int j;
    for (j = 0; j < (int)selection->count; j++)
        selection->entries[j].id = -1;
    selection->count = 0;
    switch (selection->state) {
    case 0: {
        int id;
        for (id = 6; id < 0x43; id++) {
            if (!func_0021F350(id))
                continue;
            if (func_0021F410(id))
                continue;
            if (selection->count > 0x43)
                break;
            selection->entries[selection->count++].id = id;
        }
        break;
    }
    }
    func_002200B8(selection, selection->index);
}
