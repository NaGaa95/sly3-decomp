// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

struct CommitRequest {
    unsigned char opaque00[0x1C];
    unsigned int flags;
};
struct CommitSave {
    unsigned char opaque00[0x13950];
    void *selected;
};
struct CommitMenu {
    unsigned char opaque00[0x60];
    int action;
};
struct KEY;
extern unsigned char D_0036C700[], D_00375290[], D_003751D0[], D_00468D30[];
extern struct KEY *D_00479630;
void func_001854C8(void *context, int event, void *subject);
int func_001CFDF8(void *save);
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
void func_001D0C08(void *menu, int mode);
void func_001CFD80(void *save);
void func_0018AD90(void);

void func_001D5398(struct CommitRequest *request)
{
    void *context = D_0036C700;
    struct CommitSave *save;
    struct CommitMenu *menu;
    CRef value;
    int enabled;

    func_001854C8(context, 0x3F, 0);
    func_001854C8(context, 0x40, 0);
    save = (struct CommitSave *)D_00375290;
    if (save->selected && !func_001CFDF8(save)) {
        menu = (struct CommitMenu *)D_003751D0;
        menu->action = 1;
        func_002BC010(&value, D_00479630, D_00468D30);
        enabled = value.payload.integer;
        func_0012BC20(&value);
        if (!enabled) {
            func_001D0C08(menu, 0x2F);
        } else {
            func_001D0C08(menu, 0x26);
            func_001CFD80(save);
        }
    } else {
        func_0018AD90();
    }
    if (request)
        request->flags |= 2;
}
