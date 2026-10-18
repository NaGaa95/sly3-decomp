// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
struct GameOptionKeys {
    unsigned char opaque[0x42C0];
    KEY *second;
    KEY *first;
};
extern "C" {
extern unsigned char D_00468D30[];
extern GameOptionKeys D_00475480;
extern int D_00325E00[];
OptionWriteReference QueryWriteOption(KEY *, unsigned char *) __asm__("func_002BC010");
const unsigned short *func_00150630(GameOptionKeys *game, int identifier);
unsigned short *func_00271730(unsigned short *destination, const unsigned short *source);
}
static inline int ReadInteger(KEY *key)
{
    return QueryWriteOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_0021A818(unsigned short *destination)
{
    int first = ReadInteger(D_00475480.first);
    int second = ReadInteger(D_00475480.second);
    int limit = 8;
    int level = (first * 2 + second) / 10;
    level = limit < level ? 9 : level;
    func_00271730(destination, func_00150630(&D_00475480, D_00325E00[level]));
}
