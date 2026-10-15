// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Frame;
class CRef {
public:
    short tag;
    unsigned short opaque_word2;
    union { int word; float real; void *pointer; } payload;
    CRef() { tag = -1; }
    CRef(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
};
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" {
    CRef func_0024AC98(void *object, int key, CRef *value);
    CRef func_0024AD00(void *object, int key, CRef *value);
    CRef func_0024AC18(void *object, int key, CRef *value);
    CRef func_0024AB90(void *object, int key);
    CRef func_00125E98(int count, CRef *arguments, Frame *frame, int operation);
}
CRef func_00125E98(int count, CRef *arguments, Frame *frame, int operation)
{
    CRef result;
    void *object = arguments[0].payload.pointer;
    int key = arguments[1].payload.word;
    switch (operation) {
    case 0x72:
        result = func_0024AC98(object, key, &arguments[2]);
        break;
    case 0x73:
        result = func_0024AD00(object, key, &arguments[2]);
        break;
    case 0x74:
        result = func_0024AC18(object, key, &arguments[2]);
        break;
    case 0x75:
        result = func_0024AB90(object, key);
        break;
    }
    return result;
}
