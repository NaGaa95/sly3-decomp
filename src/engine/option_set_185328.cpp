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
struct GameOptionView { unsigned char prefix[0x4084]; KEY *key; };
extern "C" {
extern unsigned char D_00468D30[];
extern unsigned char D_00475480[];
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &, unsigned char *) __asm__("func_002BC050");
void func_001853D8(char *context);
}
static inline int ClampMax(int value, int limit) { return value > limit ? limit : value; }
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
extern "C" void func_00185328(void *unused, int value)
{
    int limit = 0xF423F;
    int clamped;
    if(value < 0) clamped = 0;
    else clamped = ClampMax(value, limit);
    value = clamped;
    WriteInteger(((GameOptionView *)D_00475480)->key, value);
    func_001853D8((char *)D_00475480);
}
