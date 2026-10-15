// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Spliced methods keep the object receiver while constructing the result.
struct BasicReceiver;
class CRef {
public:
    short tag, reserved;
    union { int integer; float real; void *pointer; } payload;
    CRef(const CRef &other);
    void Decref();
    void InitTag(int kind);
    ~CRef() { Decref(); }
};
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" CRef func_0024B2B8(int count, CRef *arguments, int *types, ...);
extern "C" void func_001A0580(BasicReceiver *receiver);

extern "C" CRef func_00111E30(BasicReceiver *receiver, int argumentCount, CRef *arguments)
{
    CRef result = func_0024B2B8(0, arguments, 0);
    result.Decref();
    result.InitTag(0x22);
    func_001A0580(receiver);
    return result;
}
