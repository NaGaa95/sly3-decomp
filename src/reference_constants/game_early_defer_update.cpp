// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EvalFrame;
class CRef {
public:
    short tag, word2;
    union { int word; float real; void *pointer; } payload;
    CRef(int kind) { InitTag(kind); }
    CRef(const CRef &);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern float D_0036BB98;
extern "C" {
    CRef func_0012BAE8(CRef *input);
    void func_001C7FA8(void *object, float deadline);
}
extern "C" CRef func_00125E00(int count, CRef *arguments, EvalFrame *frame)
{
    CRef result(0x22);
    void *object = arguments[0].payload.pointer;
    float delay;
    {
        CRef converted = func_0012BAE8(&arguments[1]);
        delay = converted.payload.real;
    }
    func_001C7FA8(object, D_0036BB98 + delay);
    return result;
}
