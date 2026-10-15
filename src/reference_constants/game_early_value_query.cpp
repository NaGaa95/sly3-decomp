// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EvalFrame;
struct StatusRouter;
class CRef {
public:
    short tag, word2;
    union { int word; float real; void *pointer; } payload;
    CRef(int value) { tag = 0x13; payload.word = value; }
    CRef(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern StatusRouter D_004BC230;
extern "C" int func_00284828(StatusRouter *router, void *target, int value);
extern "C" CRef func_00125B90(int count, CRef *arguments, EvalFrame *frame)
{
    void *target = arguments[0].payload.pointer;
    int value;
    if (arguments[1].tag == 0x13)
        value = arguments[1].payload.word;
    else
        value = (int)arguments[1].payload.real;
    return CRef(func_00284828(&D_004BC230, target, value));
}
