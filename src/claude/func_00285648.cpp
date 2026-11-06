// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
typedef int qword __attribute__((mode(TI)));
class FRAME {
public:
    int x;
    FRAME();
    ~FRAME();
};
struct M4 { qword r[4]; };
struct KEY;
class IntRef {
public:
    CRef value;
    IntRef(const IntRef &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~IntRef() { Drop(); }
};
struct X { M4 m; char pad[0x94 - 0x40]; int x94; };
struct S { char pad[0x40]; int c40; X *x44; char pad2[0x1A8 - 0x48]; int x1A8; char pad3[0x2C4 - 0x1AC]; int x2C4;
           char pad4[0x2CC - 0x2C8]; int x2CC; int x2D0; int x2D4; char pad5[0x3E0 - 0x2D8]; M4 m3E0; };
extern "C" {
extern unsigned char D_00468D30[];
extern char D_00329660[], D_00329670[];
void func_001F3C48(S *p, void *pbis);
int func_001F43F0(S *p);
void func_001F43D0(S *p, int k);
int func_001F43C8(S *p);
KEY *func_0021CDA8(void *a, void *b, int c);
IntRef QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
void func_00286360(S *p, int k);
}
static inline int ReadInt(KEY *key)
{
    return QueryOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_00285648(S *p, void *pbis)
{
    FRAME frame;
    func_001F3C48(p, pbis);
    if (p->c40 > 0) {
        X *x = p->x44;
        if (!x->x94)
            p->m3E0 = x->m;
    }
    func_001F43D0(p, func_001F43F0(p));
    p->x2CC = func_001F43C8(p);
    p->x1A8 = 0;
    p->x2C4 = 0;
    p->x2D0 = -1;
    p->x2D4 = ReadInt(func_0021CDA8(D_00329660, D_00329670, 0));
    func_00286360(p, 0);
}
