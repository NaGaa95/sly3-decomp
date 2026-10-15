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
struct SampleStorage { float component[3]; };
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Sample12[(sizeof(SampleStorage) == 12) ? 1 : -1];
extern "C" CRef func_0012BAE8(CRef *input);
extern "C" CRef func_00123F98(int count, CRef *arguments, CFrame *frame)
{
    CRef result(0x1C);
    float *component = ((SampleStorage *)result.payload.pointer)->component;
    for (int i = 0; i < 3; ++i) {
        CRef value = func_0012BAE8(&arguments[i]);
        component[i] = value.payload.real;
    }
    return result;
}
