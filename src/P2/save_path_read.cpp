// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
typedef char *va_list;
#define va_start(ap,last) (ap=((char *)__builtin_next_arg(last)-(__builtin_args_info(2)>=8?0:(8-__builtin_args_info(2))*8)))
class SavePathReference {
public:
    CRef value;
    SavePathReference() { value.tag = -1; }
    SavePathReference(const SavePathReference &) __asm__("func_0012AF00");
    SavePathReference &operator=(const SavePathReference &) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~SavePathReference() { Drop(); }
};
extern "C" void func_001D2798(void *frame, int flags);
class SavePathFrame {
    int storage[4];
public:
    SavePathFrame() __asm__("func_001D2770");
    ~SavePathFrame() { func_001D2798(this, 2); }
};
struct SavePathKey { int count; short *characters; };
struct SavePathTrie;
typedef char CheckSavePathRef8[sizeof(SavePathReference) == 8 ? 1 : -1];
typedef char CheckSavePathKey8[sizeof(SavePathKey) == 8 ? 1 : -1];
typedef char CheckSavePathFrame16[sizeof(SavePathFrame) == 16 ? 1 : -1];
extern "C" {
extern SavePathTrie D_004793C8;
extern unsigned char D_00468D30[];
void func_0021CBC0(const char *, va_list, SavePathKey *);
SavePathReference func_0021C338(SavePathTrie *, SavePathKey *, unsigned char *);
}
static inline SavePathReference ReadPath(SavePathKey *key, unsigned char *buffer)
{
    return func_0021C338(&D_004793C8, key, buffer);
}
extern "C" SavePathReference func_0021CE38(const char *path, ...)
{
    SavePathReference result;
    SavePathFrame frame;
    SavePathKey key;
    va_list arguments;
    va_start(arguments, path);
    func_0021CBC0(path, arguments, &key);
    result = ReadPath(&key, D_00468D30);
    return result;
}
