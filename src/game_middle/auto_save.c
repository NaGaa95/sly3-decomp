// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

struct SaveAutoView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
};
struct KEY;
struct GameAutoView {
    unsigned char opaque00[0x41B0];
    struct KEY *query;
};
struct MenuAutoView {
    unsigned char opaque00[0x60];
    int action;
};
extern unsigned char D_00475480[], D_00468D30[];
extern unsigned char D_003751D0[], D_00375240[];
extern unsigned int D_0036DBA8;
int func_0025AE28(void *game);
int func_001CFDF8(void *save);
int func_0025E188(void);
int func_0025E150(void);
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
void func_001D0C08(void *menu, int mode);
void func_001CFD18(void *save);
void func_001D20C8(void *menu);

void func_001CFE08(void *save)
{
    struct SaveAutoView *context = save;
    struct GameAutoView *game;
    CRef value;
    int enabled;
    if (!context->selectedBlock)
        return;
    game = (struct GameAutoView *)D_00475480;
    if (func_0025AE28(game))
        return;
    if (D_0036DBA8)
        return;
    if (func_001CFDF8(save))
        return;
    if (func_0025E188() == 1 && func_0025E150() == 0x23)
        return;
    func_002BC010(&value, game->query, D_00468D30);
    enabled = value.payload.integer;
    func_0012BC20(&value);
    if (!enabled) {
        ((struct MenuAutoView *)D_003751D0)->action = 3;
        func_001D0C08(D_003751D0, 0x2F);
    } else {
        func_001CFD18(save);
        func_001D20C8(D_00375240);
    }
}
