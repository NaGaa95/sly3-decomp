// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ControlClonePair { unsigned int first, second; };
struct ControlCloneMember {
    unsigned int word0;
    ControlClonePair words04, words0C;
};
struct ControlCloneReceiver {
    unsigned char opaque00[0x158];
    ControlCloneMember member;
    unsigned char opaque16C[4];
    ControlClonePair links;
};

class KeepControlCloneMember {
    ControlCloneMember *member;
    ControlClonePair words04, words0C;
public:
    KeepControlCloneMember(ControlCloneMember *value) : member(value),
        words04(value->words04), words0C(member->words0C) {}
    ~KeepControlCloneMember() {
        member->words04 = words04;
        member->words0C = words0C;
    }
};

extern "C" void func_0023F400(void *destination, void *source);

extern "C" void func_001A1850(void *destination, void *source)
{
    ControlCloneReceiver *receiver = (ControlCloneReceiver *)destination;
    KeepControlCloneMember keep(&receiver->member);
    ControlClonePair links = receiver->links;
    func_0023F400(destination, source);
    receiver->links = links;
}
