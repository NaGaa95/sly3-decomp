// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// func_002833C8 + setter func_002834D8 (adjacent, one unit).
extern "C" {
#include "eval_dispatch_api.h"
}
struct KEY;
class IntRef {
public:
    CRef value;
    IntRef(const IntRef &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~IntRef() { Drop(); }
};
struct S { char pad[0x50]; int x50; char pad2[0x70 - 0x54]; int x70; char pad3[0x78 - 0x74]; float f78; float f7C;
           char pad4[0x84 - 0x80]; int x84; char pad5[0x9C - 0x88]; float f9C; };
extern "C" {
extern unsigned char D_00468D30[];
extern unsigned char D_004BC230[];
extern int D_003448E0;
extern int D_00375298;
extern unsigned char D_003752B4[];
int func_002835D0(S *p);
int func_002852B0(void *p);
IntRef QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
}
static inline int ReadInt(KEY *key, unsigned char *context)
{
    return QueryOption(key, context).value.payload.integer;
}
extern "C" int func_002833C8(S *p0)
{
    register S *p asm("$18") = p0; // pin: s2 for p
    unsigned char *context;
    KEY *key;
    int v;
    unsigned int i;

    if (D_003448E0)
        goto one;
    __asm__("" : "+r"(p));
    if (func_002835D0(p))
        goto one;
    context = D_00468D30;
    key = (KEY *)&p->x70;
    if (func_002852B0(D_004BC230))
        context = D_004BC230 + 0x38;
    if (!p->x70)
        goto one;
    v = ReadInt(key, context);
    if (p->x50 == 2 && D_00375298 == 6) {
        for (i = 0; i < 3; i++) {
            if (ReadInt(key, D_003752B4 + i * 0x6864)) {
                v = 1;
                break;
            }
        }
    }
    return v;
one:
    return 1;
}
extern "C" void func_002834D8(S *p, float g)
{
    p->x84 = 0;
    p->f78 = 1.0f;
    p->f9C = g;
    p->f7C = -1.0f / g;
}
