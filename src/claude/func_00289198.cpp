// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class Ref {
public:
    CRef value;
    Ref(int n) { value.tag = 0x13; value.payload.integer = n; }
    Ref(const Ref &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~Ref() { Drop(); }
};
class CTX {
    int storage[4];
public:
    CTX();
    ~CTX();
};
struct KEY;
struct LEVEL { int x0; int x4; char pad8[0x3C - 0x8]; int x3C; };
struct SW { char pad[0x4074]; KEY *key4074; KEY *key4078; KEY *key407C; KEY *key4080; };
struct GAME;
extern "C" {
extern SW D_00475480;
extern GAME D_0036C700;
extern int D_002EDFB0[];
LEVEL *func_0025E070(int);
int func_0025E4A0(int, unsigned char *);
KEY *func_0021CDA8(const char *, const char *, int);
void func_00289070(SW *, LEVEL *, int, int, int);
void func_00189E70(GAME *, LEVEL *, int, int);
}
Ref ReadOption(KEY *, unsigned char *) __asm__("func_002BC010");
Ref WriteOption(KEY *, const Ref &, unsigned char *) __asm__("func_002BC050");
static inline bool FValid(LEVEL *p) { return p && p->x4 != p->x3C; }
static inline int ReadInt(KEY *key, unsigned char *context) { return ReadOption(key, context).value.payload.integer; }
static inline void WriteInt(KEY *key, int n, unsigned char *context)
{
    Ref value(n);
    Ref argument(value);
    WriteOption(key, argument, context);
}
extern "C" void func_00289198(SW *psw, int k, int x, unsigned char *context)
{
    CTX frame;
    LEVEL *plevel = func_0025E070(D_002EDFB0[k]);
    switch (k) {
    case 6:
        if (!ReadInt(func_0021CDA8("t4_recon_complete", "is_complete", 0), context))
            plevel = func_0025E070(0x18);
        break;
    case 7: {
        KEY *pkeyTreasure = func_0021CDA8("t5_treasure_complete", "is_complete", 0);
        KEY *pkeyHeist = func_0021CDA8("t5_heist_complete", "is_complete", 0);
        if (ReadInt(pkeyTreasure, context) && !ReadInt(pkeyHeist, context))
            plevel = func_0025E070(0x20);
        break;
    }
    }
    int id = -1;
    switch (k) {
    case 1:
        if (!func_0025E4A0(1, context)) {
            id = 0x706;
            plevel = func_0025E070(0x23);
        }
        break;
    case 8: {
        WriteInt(psw->key4074, k, context);
        WriteInt(psw->key4078, k, context);
        id = ReadInt(D_00475480.key407C, context);
        if (id == -1 || id == 0)
            id = 0x731;
        else
            plevel = func_0025E070(ReadInt(D_00475480.key4080, context));
        break;
    }
    }
    int fValid;
    if (!plevel) {
        plevel = func_0025E070(0);
        if (!plevel) { fValid = 0; goto L; }
    }
    fValid = plevel->x4 != plevel->x3C;
L:
    if (!fValid)
        plevel = 0;
    if (id == -1)
        func_00289070(psw, plevel, 0x1A8, x, -1);
    else
        func_00189E70(&D_0036C700, plevel, id, x);
}
