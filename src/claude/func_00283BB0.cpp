// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// func_00283BB0: fill a save record from the game state - task keys, the level id, the GAMESAVE
// (0x6808 bytes from D_00468D30) and GAME+0x10 (0x1488 bytes) block copies, then re-writes the request's option
// (tag 0x15 CRef, read before func_0021C860 resets the options) and clears the 0x43 SW option keys for kind 2.
extern "C" {
#include "eval_dispatch_api.h"
}
class Ref {
public:
    CRef value;
    Ref(int flag) { value.tag = 0x15; value.payload.integer = flag; }
    Ref(const Ref &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~Ref() { Drop(); }
};
struct KEY { int dummy; };
struct GAMESAVE { int a[0x6808 / 4]; };
struct GAMEX { int a[0x1488 / 4]; };
struct GAME { char pad[0x10]; GAMEX x; int key0, key1, key2, n14A4; };
struct LEVEL { char pad[0xAC]; int id; };
struct SW { char pad[0x404C]; LEVEL *plevel; char pad4050[0x4088 - 0x4050]; KEY *akey[0x43]; };
struct SAVE { char pad[0x34]; int id; GAMESAVE save; GAMEX x; int key0, key1, key2; };
struct REQ { char pad[0x50]; int kind; char pad54[4]; int level; int n5C; char pad60[0xB0 - 0x60]; KEY key; };
struct TRIE;
extern "C" {
extern GAME D_0036C700;
extern SW D_00475480;
extern unsigned char D_00468D30[];
extern char D_00375290[];
extern TRIE D_004793C8;
int func_0025E150(void);
void func_001CFDE8(void *, int);
void func_0021C860(TRIE *, unsigned char *);
void *func_0025E070(int);
void func_00189E70(GAME *, void *, int, int);
void func_00283B98(SAVE *, REQ *);
void func_00283F20(SAVE *);
}
Ref ReadOption(KEY *, unsigned char *) __asm__("func_002BC010");
Ref WriteOption(KEY *, const Ref &, unsigned char *) __asm__("func_002BC050");
static inline int ReadInt(KEY *key, unsigned char *context) { return ReadOption(key, context).value.payload.integer; }
static inline void WriteBool(KEY *key, int flag, unsigned char *context)
{
    Ref value(flag);
    Ref argument(value);
    WriteOption(key, argument, context);
}
extern "C" void func_00283BB0(SAVE *psave, REQ *preq, int grf, int n)
{
    psave->key0 = D_0036C700.key0;
    psave->key1 = D_0036C700.key1;
    psave->key2 = D_0036C700.key2;
    if (D_00475480.plevel)
        psave->id = D_00475480.plevel->id;
    else
        psave->id = func_0025E150();
    psave->save = *(GAMESAVE *)D_00468D30;
    func_001CFDE8(D_00375290, 1);
    psave->x = D_0036C700.x;
    bool fKey = preq->key.dummy != 0;
    KEY *pkey = &preq->key;
    int value;
    if (fKey)
        value = ReadInt(pkey, D_00468D30);
    func_0021C860(&D_004793C8, D_00468D30);
    if (fKey)
        WriteBool(pkey, value, D_00468D30);
    if (preq->kind == 2) {
        for (int i = 0; i < 0x43; i++)
            WriteBool(D_00475480.akey[i], 0, D_00468D30);
    }
    D_0036C700.n14A4 = n;
    func_00189E70(&D_0036C700, func_0025E070(preq->level), preq->n5C, grf | 0x80);
    func_00283B98(psave, preq);
    func_00283F20(psave);
}
