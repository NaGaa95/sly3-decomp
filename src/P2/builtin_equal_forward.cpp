// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct CFrame;
class CRef {
public:
    short tag, references;
    union { int word; void *pointer; } payload;
    CRef() { tag = -1; }
    CRef(bool value) { tag = 0x15; payload.word = value; }
    CRef(const CRef &);
    CRef &operator=(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
};

extern "C" CRef func_00122220(const CRef *first, const CRef *second);

extern "C" CRef func_00122458(int count, CRef *arguments, CFrame *frame)
{
    return func_00122220(arguments, arguments + 1);
}
