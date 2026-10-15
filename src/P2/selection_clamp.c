// SLY3_CFLAGS: -Os -G0
#include "selection_types.h"

extern int D_0046FD40;
extern int D_0034939C;
int func_00220080(Selection *);
void func_0021EDC0(Selection *);

static inline int Maximum(int a, int b)
{
    return a < b ? b : a;
}

static inline int Clamp(int value, int low, int high)
{
    if (value < low)
        return low;
    if (value > high)
        return high;
    return value;
}

void func_002200B8(Selection *selection, int index)
{
    if (selection->count == 0) {
        selection->first = 0;
        selection->index = -1;
        selection->selected = -1;
    } else {
        index = Clamp(index, 0, (int)selection->count - 1);
        selection->index = index;
        if (D_0046FD40) {
            if (index < selection->first) {
                selection->first = index;
            } else {
                while (func_00220080(selection) - 1 < selection->index)
                    selection->first++;
            }
            if (selection->first == 1)
                selection->first = 0;
        } else {
            int first = Clamp(selection->first,
                Maximum(index - D_0034939C + 1, 0), index);
            selection->first = first;
        }
        selection->selected = selection->entries[selection->index].id;
    }
    func_0021EDC0(selection);
}
