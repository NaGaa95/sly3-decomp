// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "heap_frame_api.h"

struct ChoiceNode {
    unsigned char opaque00[0x20];
    ChoiceNode *next;
    unsigned char opaque24[0x40 - 0x24];
    int label;
    unsigned char opaque44[0x50 - 0x44];
    int mode;
};
struct ChoiceBucket { ChoiceNode *head; };
struct ChoiceRow {
    int label;
    void (*action)(ChoiceRow *);
    int word08;
    ChoiceNode *node;
    int word10, word14, word18;
    unsigned int flags;
};
struct ChoiceMenu { unsigned char opaque00[0x30]; int word30; };
struct ChoiceHeapFrame {
    ChoiceHeapFrame() __asm__("func_001D2770");
    ~ChoiceHeapFrame() { func_001D2798(this, 2); }
};
class ObjectToken { public: ~ObjectToken(); };
extern "C" {
extern unsigned char D_00475480[];
extern ChoiceMenu D_0046F550;
extern ChoiceRow D_003899F0[6];
extern unsigned char D_00345920[];
void *func_00292034(void *, int, unsigned int);
ChoiceBucket *func_0017DBD0(void *, int);
int func_002833C8(ChoiceNode *);
void func_001D57B8(ChoiceRow *);
void func_001D3818(void *, int, ChoiceRow *);
void func_001D3960(void *, int, ChoiceRow *, int, int);
}
typedef char ChoiceRowIs32[(sizeof(ChoiceRow) == 32) ? 1 : -1];

extern "C" void func_001D5698(ChoiceRow *request)
{
    ChoiceHeapFrame frame;
    ChoiceRow *output = D_003899F0;
    func_00292034(output, 0, 0xC0);
    ObjectToken token;
    for (ChoiceNode *node = func_0017DBD0(D_00475480, 0xAA)->head;
         node; node = node->next) {
        if (node->mode == 2 && func_002833C8(node)) {
            int label = node->label;
            output->node = node;
            output->label = label;
            output->action = func_001D57B8;
            ++output;
        }
    }
    if (request) {
        func_001D3818(&D_0046F550, output - D_003899F0, D_003899F0);
        request->flags |= 2;
    } else {
        func_001D3960(&D_0046F550, output - D_003899F0,
                     D_003899F0, D_0046F550.word30, (int)D_00345920);
    }
}
