// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, references;
    union { int word; float real; void *pointer; } payload;
    CRef(int kind) { InitTag(kind); }
    CRef(const CRef &);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" {
    CRef func_0012BAE8(CRef *input);
    void func_0011EDF8(void *curve, float start, float next, float time, float end);
    CRef func_001251B8(int count, CRef *arguments, CFrame *frame);
}
CRef func_001251B8(int count, CRef *arguments, CFrame *frame)
{
    CRef result(0x1A);
    {
        CRef first = func_0012BAE8(&arguments[0]);
        float start = first.payload.real;
        CRef second = func_0012BAE8(&arguments[1]);
        float next = second.payload.real;
        CRef third = func_0012BAE8(&arguments[2]);
        float time = third.payload.real;
        CRef fourth = func_0012BAE8(&arguments[3]);
        func_0011EDF8(result.payload.pointer, start, next, time, fourth.payload.real);
    }
    return result;
}
