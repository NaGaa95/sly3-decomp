// SLY3_CFLAGS: -Os -G0
#include "input_query_api.h"
#include "actor_resource_lookup_api.h"

struct SelectorNotifyMethod { short adjustment, reserved; void *function; };
struct SelectorNotifyView {
    unsigned char prefix[0xC];
    struct SelectorNotifyMethod *table;
    unsigned char unknown10[0x134 - 0x10];
    void *input;
    unsigned char unknown138[0x1D0 - 0x138];
    void *selector;
    void *listener;
    void *selected;
};
void func_00212770(void *, void *);

void func_0027D4E0(struct SelectorNotifyView *receiver)
{
    if (receiver->input && func_001A7A80(receiver->input, 0xFF, 0.0f)) {
        if (receiver->selector) {
            void *selected = func_001FBE30(receiver->selector, 0);
            struct SelectorNotifyMethod *method;
            if (!selected)
                return;
            receiver->selected = selected;
            if (receiver->listener)
                func_00212770(receiver->listener, selected);
            method = receiver->table + 3;
            ((void (*)(void *, int, int, int, void *, void *))method->function)
                ((char *)receiver + method->adjustment, 5, 0, 0, 0, 0);
        } else {
            struct SelectorNotifyMethod *method = receiver->table + 3;
            ((void (*)(void *, int, int, int, void *, void *))method->function)
                ((char *)receiver + method->adjustment, 5, 0, 0, 0, 0);
        }
    }
}
