// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "game_text.h"
struct ActionTextEntry {
    short delta, padding;
    int (*method)(void *, int);
};
struct ActionTextActor {
    unsigned char opaque00[12];
    ActionTextEntry *table;
};
extern "C" {
extern char D_00475480[];
extern int D_0046F568;
void *func_001F4AD0(void *unused, int index);
}
extern "C" void func_001F58E8(unsigned short *output, int selector)
{
    int selected = D_0046F568;
    if (selected != -1) {
        ActionTextActor *actor = static_cast<ActionTextActor *>(func_001F4AD0(D_00475480, selected));
        if (actor) {
            ActionTextEntry *entry = &actor->table[91];
            int identifier = entry->method(reinterpret_cast<char *>(actor) + entry->delta, selector);
            if (identifier != -1)
                func_00271730(output, func_00150630(D_00475480, identifier));
        }
    }
}
