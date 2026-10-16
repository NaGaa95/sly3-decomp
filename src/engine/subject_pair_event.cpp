// SLY3_CFLAGS: -Os -G0 -fno-exceptions
class SubjectPairEvent {
    char prefix[12];
public:
    virtual void Retain();
    virtual void Release();
    virtual void Notify(int event, int schedule, int count, void **arguments, void *result);
};
extern "C" int func_001880F0(SubjectPairEvent *);
extern "C" void func_00189DF8(SubjectPairEvent *subject, unsigned int first, unsigned int second)
{
    if (func_001880F0(subject)) {
        void *arguments[2];
        arguments[0] = &first;
        arguments[1] = &second;
        subject->Notify(0x14, 0, 2, arguments, 0);
    }
}
