// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(int integer) { value.tag = 0x13; value.payload.integer = integer; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
struct OptionKeys {
    unsigned char opaque[0x4070];
    KEY *first, *second, *third;
    unsigned char gap407C[0x4194 - 0x407C];
    KEY *primary;
};
extern "C" {
extern unsigned char D_00468D30[];
extern int D_0036B120;
extern int D_0036DBE0;
int func_0025E150(void);
int func_0025E188(void);
int func_0025E198(void *record);
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &,
                                      unsigned char *) __asm__("func_002BC050");
}
static inline void WriteOption(KEY *key, OptionWriteReference value, void *buffer)
{
    AssignWriteOption(key, value, (unsigned char *)buffer);
}
static inline void WriteInteger(KEY *key, int integer)
{
    unsigned char *context = D_00468D30;
    OptionWriteReference value(integer);
    WriteOption(key, value, context);
}
extern "C" void func_0025B6B8(OptionKeys *keys)
{
    WriteInteger(keys->primary, D_0036B120);
    WriteInteger(keys->first, func_0025E150());
    int limit = func_0025E188();
    WriteInteger(keys->second, limit);
    int mode = D_0036DBE0 ^ 2;
    if (mode && func_0025E198(D_00468D30) < limit)
        WriteInteger(keys->third, limit);
}
