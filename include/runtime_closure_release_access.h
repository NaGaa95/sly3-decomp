#ifndef SLY3_RUNTIME_CLOSURE_RELEASE_ACCESS_H
#define SLY3_RUNTIME_CLOSURE_RELEASE_ACCESS_H
extern "C" {
#include "eval_dispatch_api.h"
#include "runtime_managed_removal_access.h"

void func_002BABA8(EvalFrame *frame, int flags);
void func_002BACE0(void *receiver, int flags);
void func_002BAD40(int **reference, int flags);
void func_002BA840(void *receiver, int flags);
void func_0011E1F0(void *pool, void *allocation);
extern unsigned char D_004D2C88[];
extern unsigned char D_004D2D60[];
}

// A consumed byte view, distinct from the canonical opaque EvalFrame type.
struct RuntimeFrameCountView { unsigned int references; };
struct RuntimeEvalFrameReleaseView {
    unsigned int references;
    unsigned int links;
    EvalFrame *parent;
    RuntimeFrameCountView *bindings;
    int searching;
    int scopeFlag;
};
typedef char RuntimeEvalFrameReleaseSize24[sizeof(RuntimeEvalFrameReleaseView) == 24 ? 1 : -1];
typedef char RuntimeEvalFrameReleaseParent8[(unsigned int)&((RuntimeEvalFrameReleaseView *)0)->parent == 8 ? 1 : -1];
typedef char RuntimeEvalFrameReleaseBindings12[(unsigned int)&((RuntimeEvalFrameReleaseView *)0)->bindings == 12 ? 1 : -1];

// These three class declarations are identical to the maintained caller.
struct ClosureFrameReference {
    EvalFrame *value;
    void operator=(EvalFrame *frame) __asm__("func_002BAA50");
};
struct ClosureNodeReference {
    ScriptNode *value;
    void operator=(ScriptNode *node) __asm__("func_002BA780");
};
struct ClosureStorage {
    int references;
    unsigned int word4;
    ClosureFrameReference parent;
    int parameterCount;
    int hasRestParameter;
    ClosureNodeReference parameters;
    ClosureNodeReference body;
    void Destroy(int flags) __asm__("func_002BAC20");
};
typedef char RuntimeClosureStorageSize28[sizeof(ClosureStorage) == 28 ? 1 : -1];
typedef char RuntimeClosureStorageParameters20[(unsigned int)&((ClosureStorage *)0)->parameters == 20 ? 1 : -1];
typedef char RuntimeClosureStorageBody24[(unsigned int)&((ClosureStorage *)0)->body == 24 ? 1 : -1];
#endif
