// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct CardBlock {
    unsigned char data[0x6864];
};
struct CardContext {
    int port, slot, word8, wordC;
    int word10, word14, word18, availableBlocks, word20;
    struct CardBlock slots[3];
    unsigned char pad13950[0x13960 - 0x24 - 3 * 0x6864];
    unsigned char commandContext[1];
};
typedef char card_block_size_6864[(sizeof(struct CardBlock) == 0x6864) ? 1 : -1];
extern const char D_00323A50[], D_00323A58[], D_00323A78[], D_00323A18[], D_00323A00[];
extern unsigned char D_003751D0[];
int func_002A3050(int port, int slot, const char *name);
#include "card_commands.h"
int func_001CF7A0(void);
#include "save_bootstrap_api.h"
int func_001D0478(void *context, void *block);
void func_001CFB40(struct CardContext *context, struct CardBlock *block, char *name);
int func_001D0B08(void *context, const char *name);
void func_001D0D30(void *menu, int selection);
int func_001CF890(struct CardContext *context) {
    char name[0x50];
    int completed;
    int count;
    int result;
    void *commandContext = context->commandContext;
    count = 1;
    result = func_001CEFC8(commandContext, func_002A3050(context->port, context->slot, D_00323A50), 0x12, &completed);
    if (result == 0) {
        if (!completed) count = 2;
        count += 5;
        count += (func_001CF7A0() + 0x3FF) / 0x400;
        count += 0x51;
        if (context->availableBlocks < count) {
            result = 1;
        }
        else {
            result = func_001CF7B8(context);
            if (result == 0) {
                for (count = 0; count < 3; count++) {
                    result = func_001D0478(context, &context->slots[count]);
                    if (result) goto cleanup;
                }
                if (context->wordC < 5) context->wordC = 5;
                goto done;
            }
            cleanup: for (count = 0; count < 3; count++) {
                func_001CFB40(context, &context->slots[count], name);
                func_001D0B08(context, name);
            }
            func_001D0B08(context, D_00323A58);
            func_001D0B08(context, D_00323A78);
            func_001D0B08(context, D_00323A18);
            func_001D0B08(context, D_00323A00);
        }
    }
    if (result) func_001D0D30(D_003751D0, 3);
    done: return result;
}
