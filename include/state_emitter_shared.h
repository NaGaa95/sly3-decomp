#ifndef SLY3_STATE_EMITTER_H
#define SLY3_STATE_EMITTER_H
#include "common.h"
struct Matrix4 { qword row[4]; };
struct VirtualEntry {
    short delta,word2;
    union {
        void (*call)(void *);
        void (*simple)(void *);
        struct Matrix4 *(*matrix)(void *);
    };
};
struct Actor { char prefix[0xC];struct VirtualEntry *table; };
struct PositionRequest {
    void *anchor;struct Actor *actor;char padding[8];qword position;
};
struct EmittedObject;
struct StateEmitter {
    char prefix[0xC];struct VirtualEntry *table;
    struct Actor *owner;void *previous;
    struct EmittedObject *retainedChild;int word1C,nestedCount;
    char pad24[0xC];struct Actor *actor;char pad34[0xC];
    qword localPosition;int state;float changedAt;
    char pad58[8];qword lastPosition;
};
typedef char state_emitter_size112[(sizeof(struct StateEmitter)==112)?1:-1];
typedef char position_request_size32[(sizeof(struct PositionRequest)==32)?1:-1];
typedef char matrix_rows_size64[(sizeof(struct Matrix4)==64)?1:-1];
// These three contracts are used by both state creation and subsequent update.
#ifdef __cplusplus
extern "C" {
#endif
void func_002B8750(struct PositionRequest *request);
void func_001D7FD0(struct EmittedObject *object, const struct PositionRequest *request);
qword func_001C9428(struct Actor *source, struct Actor *destination, qword position);
#ifdef __cplusplus
}
#endif
#endif
