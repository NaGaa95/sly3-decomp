// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ClonePreservedPair { unsigned int first, second; };
struct ClonePreservedMember {
    unsigned int word0;
    ClonePreservedPair words04, words0C;
};
struct ClonePreservedReceiver {
    unsigned char opaque00[0xF8];
    ClonePreservedMember member;
    unsigned char opaque10C[8];
    ClonePreservedPair links;
};

class KeepCloneMember {
    ClonePreservedMember *member;
    ClonePreservedPair words04, words0C;
public:
    KeepCloneMember(ClonePreservedMember *value) : member(value),
        words04(value->words04), words0C(member->words0C) {}
    ~KeepCloneMember() {
        member->words04 = words04;
        member->words0C = words0C;
    }
};

extern "C" void func_0028FE20(void *destination, void *source);

extern "C" void func_001A10C0(void *destination, void *source)
{
    ClonePreservedReceiver *receiver = (ClonePreservedReceiver *)destination;
    KeepCloneMember keep(&receiver->member);
    ClonePreservedPair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}

extern "C" void func_001A1570(void *destination, void *source)
{
    ClonePreservedReceiver *receiver = (ClonePreservedReceiver *)destination;
    KeepCloneMember keep(&receiver->member);
    ClonePreservedPair links = receiver->links;
    func_0028FE20(destination, source);
    receiver->links = links;
}
