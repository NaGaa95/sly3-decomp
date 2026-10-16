// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ExtraClonePair { unsigned int first, second; };
struct ExtraCloneMember {
    unsigned int word0;
    ExtraClonePair words04, words0C;
};
struct ExtraCloneF8 {
    unsigned char opaque00[0xF8];
    ExtraCloneMember member;
    unsigned char opaque10C[8];
    ExtraClonePair links;
};
struct ExtraClone148 {
    unsigned char opaque00[0x148];
    ExtraCloneMember member;
    unsigned char opaque15C[8];
    ExtraClonePair links;
};
struct ExtraClone158 {
    unsigned char opaque00[0x158];
    ExtraCloneMember member;
    unsigned char opaque16C[4];
    ExtraClonePair links;
};
struct ExtraCloneD0 {
    unsigned char opaque00[0xD0];
    ExtraCloneMember member;
    unsigned char opaqueE4[0x140 - 0xE4];
    ExtraClonePair links;
};

class KeepExtraCloneMember {
    ExtraCloneMember *member;
    ExtraClonePair words04, words0C;
public:
    KeepExtraCloneMember(ExtraCloneMember *value) : member(value),
        words04(value->words04), words0C(member->words0C) {}
    ~KeepExtraCloneMember() {
        member->words04 = words04;
        member->words0C = words0C;
    }
};

extern "C" void func_0028FE20(void *destination, void *source);
extern "C" void func_0023F400(void *destination, void *source);

extern "C" void func_001A1F20(void *destination, void *source)
{
    ExtraCloneF8 *receiver = (ExtraCloneF8 *)destination;
    KeepExtraCloneMember keep(&receiver->member);
    ExtraClonePair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}

extern "C" void func_001A2510(void *destination, void *source)
{
    ExtraClone148 *receiver = (ExtraClone148 *)destination;
    KeepExtraCloneMember keep(&receiver->member);
    ExtraClonePair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}

extern "C" void func_001A2828(void *destination, void *source)
{
    ExtraClone158 *receiver = (ExtraClone158 *)destination;
    KeepExtraCloneMember keep(&receiver->member);
    ExtraClonePair links = receiver->links;
    func_0023F400(destination, source);
    receiver->links = links;
}

extern "C" void func_001A3438(void *destination, void *source)
{
    ExtraCloneD0 *receiver = (ExtraCloneD0 *)destination;
    KeepExtraCloneMember keep(&receiver->member);
    ExtraClonePair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}
