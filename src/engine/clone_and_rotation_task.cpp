// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/matrix_algorithms.h"
#include "resource_attachment_api.h"
struct EngineStateClonePair { unsigned int first, second; };
struct EngineStateCloneMember {
    unsigned int word0;
    EngineStateClonePair words04, words0C;
};
struct EngineStateCloneReceiver {
    unsigned char unaccessed0[0x210];
    EngineStateCloneMember member;
    unsigned char unaccessed224[8];
    EngineStateClonePair links;
};
class PreserveEngineStateCloneMember {
    EngineStateCloneMember *member;
    EngineStateClonePair words04, words0C;
public:
    PreserveEngineStateCloneMember(EngineStateCloneMember *value) :
        member(value), words04(value->words04), words0C(member->words0C) {}
    ~PreserveEngineStateCloneMember() {
        member->words04 = words04;
        member->words0C = words0C;
    }
};
extern "C" void func_0028FE20(void *destination, void *source);
extern "C" void func_0015CDC8(void *destination, void *source)
{
    EngineStateCloneReceiver *receiver = (EngineStateCloneReceiver *)destination;
    PreserveEngineStateCloneMember keep(&receiver->member);
    EngineStateClonePair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}
struct EngineRotationTaskReceiver {
    unsigned char unaccessed0[0x10];
    void *owner;
    unsigned char unaccessed14[0xF0-0x14];
    void *task;
    unsigned char unaccessedF4[12];
    EE_ATTACHMENT_QWORD rotation;
};
extern "C" void *func_0023DDA0(void *owner, int identity, int kind);
extern "C" void func_00135288(EngineRotationTaskReceiver *receiver)
{
    void *channel = func_0023DDA0(receiver->owner, 0x3A, 6);
    if (channel) {
        EE_ATTACHMENT_QWORD rotation = func_0011D3C0((const MATRIX3 *)channel);
        receiver->rotation = rotation;
        receiver->task = func_00130078(receiver->owner, channel, 3, 8, 2, rotation);
    }
}
