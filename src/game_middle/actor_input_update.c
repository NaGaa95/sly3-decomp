// SLY3_CFLAGS: -Os -G0
#include "input_query_api.h"
struct ActorInputUpdate {
    char prefix[0x134];
    void *input;
    char reserved138[0x194 - 0x138];
    int state;
    char reserved198[0x1C0 - 0x198];
    unsigned int selection;
};
void func_0023C660(void *receiver);
void func_001E8E60(void *receiver, int state);
void func_001E8F38(void *receiver);

void func_001E8D80(void *receiver)
{
    struct ActorInputUpdate *p = receiver;
    int previous;
    func_0023C660(receiver);
    do {
        previous = p->state;
        if (previous == 0) {
            unsigned int pressed = func_001A7A80(p->input, 0x30, 0.15f);
            if (pressed) {
                p->selection = pressed & 0x10;
                func_001E8E60(receiver, 1);
            }
        }
    } while (p->state != previous);
    if (p->state == 0) func_001E8F38(receiver);
}
