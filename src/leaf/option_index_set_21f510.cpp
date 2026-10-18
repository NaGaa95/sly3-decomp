// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(int tag, int bits) { value.tag = tag; value.payload.integer = bits; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
struct GameOptionKeys {
    unsigned char prefix[0x4088];
    KEY *keys[1];
};
struct RequestContext {
    unsigned char prefix[0xC];
    int selected;
};
extern "C" {
extern GameOptionKeys D_00475480;
extern RequestContext D_0036C700;
extern unsigned char D_00468D30[];
void func_001854C8(void *context, int event, void *payload);
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &,
                                      unsigned char *) __asm__("func_002BC050");
}
static inline void WriteOption(KEY *key, OptionWriteReference value, void *buffer)
{
    AssignWriteOption(key, value, (unsigned char *)buffer);
}
static inline void WriteBooleanBits(KEY *key, int bits)
{
    unsigned char *context = D_00468D30;
    OptionWriteReference value(0x15, bits);
    WriteOption(key, value, context);
}
extern "C" void func_0021F510(int index, int enabled)
{
    WriteBooleanBits(D_00475480.keys[index], enabled != 0);
    if (enabled) {
        D_0036C700.selected = index;
        func_001854C8(&D_0036C700, 0x4C, 0);
    }
}
