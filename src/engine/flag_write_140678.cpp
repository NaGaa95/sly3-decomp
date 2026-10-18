// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
#include "heap_frame_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(bool flag) { value.tag=0x15; value.payload.integer=flag; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
class WriteHeapFrame {
public:
    WriteHeapFrame() __asm__("func_001D2770");
    ~WriteHeapFrame() { func_001D2798(this, 2); }
};
struct KEY;
extern "C" {
extern unsigned char D_00468D30[];
extern const char D_0031FF98[], D_0031FFA8[];
void *func_0021CDA8(const void *name, ...);
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &, unsigned char *) __asm__("func_002BC050");
}
static inline void WriteOption(KEY *key, const OptionWriteReference &value, void *context)
{
    OptionWriteReference argument(value);
    AssignWriteOption(key, argument, (unsigned char *)context);
}
static inline void WriteBool(KEY *key, bool flag)
{
    unsigned char *context = D_00468D30;
    OptionWriteReference value(flag);
    WriteOption(key, value, context);
}
extern "C" void func_00140678(void *unused, int enabled)
{
    WriteHeapFrame frame;
    WriteBool((KEY *)func_0021CDA8(D_0031FF98, D_0031FFA8, 0), enabled != 0);
}
