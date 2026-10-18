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
struct OptionTable {
    int first;
    unsigned char gap4[0x350];
    KEY *keys[1];
};
extern "C" {
extern OptionTable D_004793C8;
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &,
                                      unsigned char *) __asm__("func_002BC050");
}
static inline void WriteOption(KEY *key, OptionWriteReference value, void *buffer)
{
    AssignWriteOption(key, value, (unsigned char *)buffer);
}
static inline void WriteBooleanBits(KEY *key, int bits, void *context)
{
    OptionWriteReference value(0x15, bits);
    WriteOption(key, value, context);
}
extern "C" void func_0025E2B8(int bits, int index, unsigned char *buffer)
{
    if (D_004793C8.first) {
        KEY *key = D_004793C8.keys[index];
        if (key)
            WriteBooleanBits(key, bits, buffer);
    }
}
