// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct PreservedPair { unsigned int first, second; };
struct PreservedContext {
    unsigned int value;
    PreservedPair words04, words0C;
};
struct PreservedReceiver {
    unsigned char opaque00[0x1A8];
    PreservedContext context;
    unsigned char opaque1BC[8];
    PreservedPair links;
};

class KeepContextPairs {
    PreservedContext *context;
    PreservedPair words04, words0C;
public:
    KeepContextPairs(PreservedContext *value) : context(value),
        words04(value->words04), words0C(context->words0C) {}
    ~KeepContextPairs() {
        context->words04 = words04;
        context->words0C = words0C;
    }
};

struct S;
extern "C" void func_0022D740(S *destination, void *source);

extern "C" void func_001F3218(void *destination, void *source)
{
    PreservedReceiver *receiver = (PreservedReceiver *)destination;
    KeepContextPairs keep(&receiver->context);
    PreservedPair links = receiver->links;
    func_0022D740((S *)destination, source);
    receiver->links = links;
}
