// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CFrame;
class CRef {
public:
    short tag, word2;
    union { int word; float real; void *pointer; } payload;
    CRef(float value) { tag = 0x14; payload.real = value; }
    CRef(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" CRef func_0012BAE8(CRef *input);
extern "C" CRef func_00125928(int count, CRef *arguments, CFrame *frame)
{
    CRef first = func_0012BAE8(&arguments[0]);
    float weight = first.payload.real;
    CRef second = func_0012BAE8(&arguments[1]);
    float start = second.payload.real;
    CRef third = func_0012BAE8(&arguments[2]);
    return CRef((1.0f - weight) * start + weight * third.payload.real);
}
