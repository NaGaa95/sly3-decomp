// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, references;
    union { int word; float real; void *pointer; } payload;
    CRef() { tag = -1; }
    CRef(const CRef &);
    CRef &operator=(float value);
    CRef &operator=(int value);
    void Decref();
    ~CRef() { Decref(); }
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" {
    CRef func_0012BAE8(CRef *value);
    int func_0011E8F0(int minimum, int maximum);
    float func_0011E940(float minimum, float maximum);
    CRef func_00124140(int count, CRef *arguments, CFrame *frame);
}
CRef func_00124140(int count, CRef *arguments, CFrame *frame)
{
    CRef result;
    if (arguments[0].tag == 0x13 && arguments[1].tag == arguments[0].tag) {
        result = func_0011E8F0(arguments[0].payload.word, arguments[1].payload.word);
    } else {
        float minimum = func_0012BAE8(&arguments[0]).payload.real;
        float maximum = func_0012BAE8(&arguments[1]).payload.real;
        result = func_0011E940(minimum, maximum);
    }
    return result;
}
