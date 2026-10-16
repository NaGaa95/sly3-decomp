#ifndef SLY3_ACTION_QUERY_SHARED_H
#define SLY3_ACTION_QUERY_SHARED_H
#include "scene.h"
#include "mat.h"
extern "C" {
#include "owned_record_list_api.h"
}

struct ActionQueryRangeView {
    float low, high;
};
struct ActionQueryScopeRecord {
    char unknown[0x10];
    void *context;
};
struct ActionQueryScopeLink {
    char unknown[0xDC];
    ActionQueryScopeRecord *record;
};
struct ActionQuerySettings {
    char unknown[0xC];
    SCENE_OBJECT *reference;
    int kind;
    float angle14, angle18;
};
struct ActionQueryOwner {
    SCENE_OBJECT scene;
    char unknown68[0xD8-0x68];
    ActionQueryScopeLink *link;
    char unknownDC[0x29C-0xDC];
    ActorOwnedRecordList actions;
    char unknown2A8[0x354-0x2A8];
    ActionQueryRangeView radius;
    char unknown35C[0x3D8-0x35C];
    ActionQuerySettings *settings;
    char unknown3DC[0x1144-0x3DC];
    int flags1144;
};
struct ActionQueryChild {
    char unknown[0x50];
    float distance;
    char unknown54[0x90-0x54];
    qword position;
};
struct ActionQueryState {
    char prefix[0x10];
    ActionQueryOwner *owner;
    char unknown14[4];
    ActionQueryChild *child;
    char unknown1C[0x30-0x1C];
    int mode;
    char unknown34[0x40-0x34];
};
typedef char ActionQueryScenePrefix68[(sizeof(SCENE_OBJECT)==0x68)?1:-1];
typedef char ActionQueryState40[(sizeof(ActionQueryState)==0x40)?1:-1];
#define ACTION_QUERY_OFFSET(type, field) ((unsigned int)&(((type *)0)->field))
typedef char ActionQueryOwnerOffsets[(ACTION_QUERY_OFFSET(ActionQueryOwner, link)==0xD8 &&
    ACTION_QUERY_OFFSET(ActionQueryOwner, actions)==0x29C &&
    ACTION_QUERY_OFFSET(ActionQueryOwner, radius)==0x354 &&
    ACTION_QUERY_OFFSET(ActionQueryOwner, settings)==0x3D8 &&
    ACTION_QUERY_OFFSET(ActionQueryOwner, flags1144)==0x1144)?1:-1];
typedef char ActionQueryStateOffsets[(ACTION_QUERY_OFFSET(ActionQueryState, owner)==0x10 &&
    ACTION_QUERY_OFFSET(ActionQueryState, child)==0x18 &&
    ACTION_QUERY_OFFSET(ActionQueryState, mode)==0x30)?1:-1];
typedef char ActionQueryChildOffsets[(ACTION_QUERY_OFFSET(ActionQueryChild, distance)==0x50 &&
    ACTION_QUERY_OFFSET(ActionQueryChild, position)==0x90)?1:-1];
#undef ACTION_QUERY_OFFSET
extern "C" {
extern const float D_00344FB8;
void func_00238978(void);
void func_002389A0(void *);
float func_00256368(ActionQuerySettings *);
void func_00120B00(qword vector, float *pan, float *radius, float *z);
float func_0011E3B8(float angle);
int func_0011EE30(const ActionQueryRangeView *, float value);
qword func_00182068(ActionQueryState *, void *context, qword target, float bearing);
void *func_001EF038(qword first, qword second, void *context);
void func_001D8B40(ActionQueryChild *, void *query);
void func_001825C0(ActionQueryState *, int mode, void *query);
}
#endif
