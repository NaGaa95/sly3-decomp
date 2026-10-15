// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionReference {
public:
    CRef value;
    OptionReference(const OptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReference() { Drop(); }
};
typedef char OptionReferenceSizeIsEight[(sizeof(OptionReference) == 8) ? 1 : -1];
struct KEY;
struct FirstInputKeys {
    unsigned char opaque[0x1148];
    KEY *keys[0];
};
struct SecondInputKeys {
    unsigned char opaque[0x1164];
    KEY *keys[0];
};
struct InputControllerStorage {
    union {
        unsigned char bytes[0x11C0];
        FirstInputKeys first;
        SecondInputKeys second;
    };
};
extern "C" {
extern KEY *D_00479618;
extern unsigned char D_00468D30[];
extern int D_00475000, D_0046F568, D_003899E8;
extern InputControllerStorage D_0036E740[];
OptionReference QueryMenuOption(KEY *key, unsigned char *buffer)
    __asm__("func_002BC010");
int func_00210DE0(void *value);
}
static inline int OptionValue(KEY *key)
{
    return QueryMenuOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_001D3DF0(int *kind)
{
    switch (*kind) {
    case 0x4E:
        break;
    case 0x5C: case 0x5D: case 0x5E:
        switch (OptionValue(D_00479618)) {
        case 1: *kind = 0x5C; break;
        case 2: *kind = 0x5D; break;
        case 0:
        default: *kind = 0x5E; break;
        }
        break;
    case 0x5F: case 0x60:
        *kind = D_00475000 ? 0x5F : 0x60;
        break;
    case 0x58: case 0x59:
        if (D_0046F568 != -1) {
            if (func_00210DE0(D_0036E740[D_0046F568].bytes + 0x1124))
                *kind = 0x58;
            else
                *kind = 0x59;
        }
        break;
    case 0x8F: case 0x90:
        if (D_0046F568 != -1) {
            KEY *key = D_0036E740[D_0046F568].first.keys[D_003899E8];
            *kind = key && OptionValue(key) ? 0x90 : 0x8F;
        }
        break;
    case 0x91: case 0x92:
        if (D_0046F568 != -1) {
            KEY *key = D_0036E740[D_0046F568].second.keys[D_003899E8];
            *kind = key && OptionValue(key) ? 0x92 : 0x91;
        }
        break;
    }
}
