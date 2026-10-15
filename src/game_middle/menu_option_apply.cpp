// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(int integer) { value.tag = 0x13; value.payload.integer = integer; }
    OptionWriteReference(float real) { value.tag = 0x14; value.payload.real = real; }
    OptionWriteReference(int tag, int bits) { value.tag = tag; value.payload.integer = bits; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
struct FirstInputKeys { unsigned char opaque[0x1148]; KEY *keys[0]; };
struct SecondInputKeys { unsigned char opaque[0x1164]; KEY *keys[0]; };
struct InputControllerStorage {
    union {
        unsigned char bytes[0x11C0];
        FirstInputKeys first;
        SecondInputKeys second;
    };
};
struct Calibration { unsigned char opaque[0x24]; float x, y; };
struct GameOptionKeys { unsigned char opaque[0x41A8]; KEY *x, *y; };
extern "C" {
extern KEY *D_00479618, *D_0047961C, *D_00479620, *D_00479624;
extern unsigned char D_00468D30[];
extern float D_00475144, D_00475140;
extern Calibration D_0036DBE0;
extern GameOptionKeys D_00475480;
extern int D_0046F568, D_003899E8;
extern InputControllerStorage D_0036E740[];
OptionWriteReference QueryWriteOption(KEY *, unsigned char *) __asm__("func_002BC010");
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &,
                                      unsigned char *) __asm__("func_002BC050");
void func_0021D360(void *buffer);
void func_001D2ED0(void *owner, int mode);
void func_00210E58(void *input, int enabled);
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
static inline void WriteReal(KEY *key, float real)
{
    unsigned char *context = D_00468D30;
    OptionWriteReference value(real);
    WriteOption(key, value, context);
}
static inline void WriteBooleanBits(KEY *key, int bits)
{
    unsigned char *context = D_00468D30;
    OptionWriteReference value(0x15, bits);
    WriteOption(key, value, context);
}
static inline int ReadInteger(KEY *key)
{
    return QueryWriteOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_001D3FC0(void *owner, int *kind)
{
    switch (*kind) {
    case 0x77:
        WriteReal(D_0047961C, 1.0f - D_00475144);
        func_0021D360(D_00468D30);
        func_001D2ED0(owner, 9);
        break;
    case 0x78:
        WriteReal(D_00479620, 1.0f - D_00475140);
        func_0021D360(D_00468D30);
        func_001D2ED0(owner, 9);
        break;
    case 0x5E:
        WriteInteger(D_00479618, 0);
        func_0021D360(D_00468D30);
        break;
    case 0x5D:
        WriteInteger(D_00479618, 2);
        func_0021D360(D_00468D30);
        break;
    case 0x4E:
        WriteReal(D_00475480.x, D_0036DBE0.x);
        WriteReal(D_00475480.y, D_0036DBE0.y);
        func_001D2ED0(owner, 9);
        break;
    case 0x5C:
        WriteInteger(D_00479618, 1);
        func_0021D360(D_00468D30);
        break;
    case 0x5F: case 0x60:
        WriteBooleanBits(D_00479624, *kind == 0x5F);
        func_0021D360(D_00468D30);
        break;
    case 0x58: case 0x59:
        if (D_0046F568 != -1)
            func_00210E58(D_0036E740[D_0046F568].bytes + 0x1124,
                           *kind != 0x59);
        break;
    case 0x8F: case 0x90:
        if (D_0046F568 != -1) {
            KEY *key = D_0036E740[D_0046F568].first.keys[D_003899E8];
            if (key)
                WriteBooleanBits(key, ReadInteger(key) ^ 1);
        }
        break;
    case 0x91: case 0x92:
        if (D_0046F568 != -1) {
            KEY *key = D_0036E740[D_0046F568].second.keys[D_003899E8];
            if (key)
                WriteBooleanBits(key, ReadInteger(key) ^ 1);
        }
        break;
    }
}
