// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct ControllerActivationPair { int first, second; };
struct ControllerActivationRecord { int word[4]; };
struct ControllerActivationView {
    char prefix[12]; SCENE_VIRTUAL_ENTRY *table;
    char pad10[0xD0 - 0x10];
    int requestCount;
    ControllerActivationRecord requests[4];
    int messageCount;
    ControllerActivationPair messages[4];
    int linkCount;
    ControllerActivationPair links[4];
    int aliasCount;
    int aliases[4];
    void *related;
};
struct ControllerActivationGame {
    char prefix[0x3EB8];
    int activeCount;
    void *providers[5];
};
typedef char CheckGamePrefix3ED0[sizeof(ControllerActivationGame) == 0x3ED0 ? 1 : -1];
struct ControllerSelectedState { char prefix[0x128]; int state; };
typedef char CheckControllerPrefix174[sizeof(ControllerActivationView) == 0x174 ? 1 : -1];
typedef char CheckRequestRecord16[sizeof(ControllerActivationRecord) == 16 ? 1 : -1];
extern "C" {
extern ControllerActivationGame D_00475480;
extern char D_0036C700[];
void *func_0017E1B8(void *, int, int, void *);
void func_001C8FB0(SCENE_OBJECT *, SCENE_OBJECT *);
void func_0025D3F8(void *, int, ControllerActivationRecord *, void *, int);
void func_00185908(void *, int, ControllerActivationPair *, void *);
int func_0017E208(void *, int, int, void *, int, ControllerSelectedState **);
void func_0027FC08(ControllerSelectedState *, int);
void func_00166548(void *);
void func_00226010(void *);
}
extern "C" void func_00280010(ControllerActivationView *controller)
{
    ControllerSelectedState *selected[32];
    for (int i = 0; i < controller->linkCount; ++i) {
        ControllerActivationPair *pair = &controller->links[i];
        SCENE_OBJECT *first = static_cast<SCENE_OBJECT *>(
            func_0017E1B8(&D_00475480, 4, pair->first, controller));
        if (first) {
            SCENE_OBJECT *second = static_cast<SCENE_OBJECT *>(
                func_0017E1B8(&D_00475480, 4, pair->second, controller));
            if (second) func_001C8FB0(first, second);
        }
    }
    func_0025D3F8(&D_00475480, controller->requestCount, controller->requests, controller, 1);
    func_00185908(D_0036C700, controller->messageCount, controller->messages, controller);
    for (int i = func_0017E208(&D_00475480, 5, 0x18, 0, 32, selected) - 1; i >= 0; --i) {
        if (selected[i]->state != 2) func_0027FC08(selected[i], 0);
    }
    for (int i = 0; i < D_00475480.activeCount; ++i) {
        func_00166548(D_00475480.providers[i]);
    }
    SCENE_VIRTUAL_ENTRY *entry = &controller->table[3];
    ((void (*)(void *, int, int, int, void *, int))entry->Simple)(
        reinterpret_cast<char *>(controller) + entry->delta, 5, 0, 0, 0, 0);
    if (controller->related) func_00226010(controller->related);
}
