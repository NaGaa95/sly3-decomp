// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ClonePair { unsigned int first,second; };
struct CloneMember {
    unsigned int word0;
    ClonePair words04,words0C;
};
struct CloneReceiver {
    unsigned char unaccessed0[0xF8];
    CloneMember member;
    unsigned char unaccessedC[8];
    ClonePair links;
};
class PreserveCloneMember {
    CloneMember *member;
    ClonePair words04,words0C;
public:
    PreserveCloneMember(CloneMember *value) :
        member(value),words04(value->words04),words0C(member->words0C) {}
    ~PreserveCloneMember() {
        member->words04=words04;
        member->words0C=words0C;
    }
};
extern "C" void func_0028FE20(void *destination,void *source);
extern "C" void func_002494B8(void *destination,void *source)
{
    CloneReceiver *receiver=(CloneReceiver *)destination;
    PreserveCloneMember keep(&receiver->member);
    ClonePair links=receiver->links;
    func_0028FE20(destination,source);
    receiver->links=links;
}
