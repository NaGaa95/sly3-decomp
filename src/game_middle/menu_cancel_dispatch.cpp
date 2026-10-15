// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class MenuCancelReference {
public:
    CRef value;
    MenuCancelReference(bool enabled) {
        value.tag = 0x15;
        value.payload.integer = enabled;
    }
    MenuCancelReference(const MenuCancelReference &other) {
        func_0012AF00(&value, &other.value);
    }
    void Drop() __asm__("func_0012BC20");
    ~MenuCancelReference() { Drop(); }
};
struct MenuState;
struct KEY;
struct MenuCancelView {
    unsigned char opaque00[0x50];
    int mode;
    unsigned char opaque54[0x60 - 0x54];
    int action;
};
struct MenuCancelPanel {
    unsigned char opaque00[0x50];
    int mode;
};
extern "C" {
extern unsigned char D_0046FC30[], D_0046F550[], D_00468D30[], D_00375290[];
extern KEY *D_00479630;
int func_0021DD30(void *);
int func_001D46B0(void *);
void func_001D0C88(MenuState *);
void func_001D0D30(MenuState *, int);
void func_001D3AE8(void *);
void func_00221EC0(void *);
int func_001D4658(void *);
void func_001D3A90(void *);
int func_001D47C0(void *);
void func_001D3918(void *);
void func_001D0C08(MenuState *, int);
void func_001CFD80(void *);
MenuCancelReference AssignMenuCancelFlag(KEY *, const MenuCancelReference &,
                                         unsigned char *) __asm__("func_002BC050");
}
static inline void SendMenuCancelFlag(KEY *key, MenuCancelReference value,
                                      unsigned char *context)
{
    AssignMenuCancelFlag(key, value, context);
}

extern "C" void func_001D1190(MenuState *receiver)
{
    MenuCancelView *state = (MenuCancelView *)receiver;
    switch (state->mode) {
    case 0x1A: case 0x1B: case 0x1D: case 0x20: case 0x23: case 0x24: {
        {
            unsigned char *panel = D_0046FC30;
            if (func_0021DD30(panel) && func_001D46B0(D_0046F550)) {
                func_001D0C88(receiver);
                func_001D0D30(receiver, 2);
                func_001D3AE8(D_0046F550);
                func_00221EC0(panel);
                break;
            }
        }
        if (((MenuCancelPanel *)D_0046FC30)->mode) {
            func_001D0C88(receiver);
            func_001D0D30(receiver, 2);
            func_00221EC0(D_0046FC30);
            break;
        }
    }
    case 0x1C: case 0x1F: case 0x22: case 0x29:
    case 0x30: case 0x31: case 0x3B:
        func_001D0C88(receiver);
        func_001D0D30(receiver, 2);
        if (func_001D4658(D_0046F550))
            func_001D3A90(D_0046F550);
        if (func_001D47C0(D_0046F550))
            func_001D3918(D_0046F550);
        break;
    case 0x27: case 0x28: case 0x2D:
        func_001D0C88(receiver);
        break;
    case 0x2F: {
        {
            KEY *key = D_00479630;
            unsigned char *context = D_00468D30;
            MenuCancelReference enabled(true);
            SendMenuCancelFlag(key, enabled, context);
        }
        if (state->action < 4) {
            if (state->action > 0) {
                func_001D0C08(receiver, 0x26);
                func_001CFD80(D_00375290);
            }
        }
        break;
    }
    }
}

struct PMF { short delta, pad; int (*pfn)(void *); };
extern "C" int func_001CF710(void *);
extern "C" const PMF D_00323D18 = { 0, -1, func_001CF710 };
