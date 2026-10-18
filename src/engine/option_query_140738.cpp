// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
#include "heap_frame_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
class QueryHeapFrame {
public:
    QueryHeapFrame() __asm__("func_001D2770");
    ~QueryHeapFrame() { func_001D2798(this, 2); }
};
struct KEY;
extern "C" {
extern unsigned char D_00468D30[];
extern const char D_0031FF98[], D_0031FFA8[];
void *func_0021CDA8(const void *name, ...);
OptionWriteReference QueryWriteOption(KEY *, unsigned char *) __asm__("func_002BC010");
}
static inline int ReadInteger(KEY *key)
{
    return QueryWriteOption(key, D_00468D30).value.payload.integer;
}
extern "C" int func_00140738(void)
{
    QueryHeapFrame frame;
    return ReadInteger((KEY *)func_0021CDA8(D_0031FF98, D_0031FFA8, 0)) != 0;
}
