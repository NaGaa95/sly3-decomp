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
struct KEY {
    int first;
};
struct OptionReceiver {
    unsigned char prefix[0x20];
    KEY *key;
};
extern "C" {
extern unsigned char D_00468D30[];
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
extern "C" void func_00210ED8(OptionReceiver *receiver, int enabled)
{
    KEY *key = receiver->key;
    if (key && key->first)
        WriteBooleanBits(key, enabled == 0);
}
