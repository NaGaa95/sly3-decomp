// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Raise a stored float option to a new maximum (CRef write pattern as in src/engine/option_message_171aa0.cpp).
extern "C" {
#include "eval_dispatch_api.h"
}
class FloatRef {
public:
    CRef value;
    FloatRef(float real) { value.tag = 0x14; value.payload.real = real; }
    FloatRef(const FloatRef &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~FloatRef() { Drop(); }
};
struct KEY;
extern "C" {
extern unsigned char D_00468D30[];
FloatRef AssignWriteOption(KEY *, const FloatRef &, unsigned char *) __asm__("func_002BC050");
}
struct X { char pad[0x50]; int x50; char pad2[0xA4 - 0x54]; float fA4; char keyA8[1]; };
struct S { char pad[0x14]; X *x14; char pad2[4]; float f1C; };
static inline void WriteOption(KEY *key, FloatRef value, void *buffer)
{
    AssignWriteOption(key, value, (unsigned char *)buffer);
}
static inline void WriteFloat(KEY *key, float real)
{
    unsigned char *context = D_00468D30;
    FloatRef value(real);
    WriteOption(key, value, context);
}
extern "C" void func_00284778(S *p)
{
    X *x = p->x14;
    int k = x ? x->x50 : -1;
    if (k == 0 && x->fA4 < p->f1C) {
        x->fA4 = p->f1C;
        WriteFloat((KEY *)p->x14->keyA8, p->f1C);
    }
}
