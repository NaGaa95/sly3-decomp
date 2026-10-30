// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(int integer) { value.tag = 0x13; value.payload.integer = integer; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
struct LinkA { unsigned char pad[0xF0]; int f0; int f4; };
struct Obj { unsigned char pad[0x18]; int x18; unsigned char pad1C[0x44 - 0x1C]; int x44; unsigned char pad48[0x6C - 0x48]; LinkA *link;
    unsigned char pad70[0xAC - 0x70]; int xAC; unsigned char padB0[0xFC - 0xB0]; int fc; int f100; };
struct Game { unsigned char pad[0x4044]; void *x4044; unsigned char pad4048[0x407C - 0x4048]; KEY *x407C; KEY *x4080; };
extern "C" {
extern unsigned char D_00468D30[];
extern Game D_00475480;
extern unsigned char D_004BC230[];
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &, unsigned char *) __asm__("func_002BC050");
int func_002852B0(void *);
Obj *func_0017E1B8(Game *, int, int, int);
void func_00187118(void *);
int func_0025E188(void);
void func_001890B0(Obj *, int, int);
int func_0025E070(int);
void func_00289070(Game *, int, int, int, int);
int func_002459F8(int);
void func_00244F08(int, int);
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
class Override {
public:
    LinkA *a;
    Obj *b;
    int aF0;
    int bFC;
    int aF4;
    int b100;
    Override(Obj *obj)
    {
        a = obj->link;
        b = obj;
        bFC = b->fc;
        b->fc = 4;
        b100 = b->f100;
        b->f100 = 0;
        if (a) {
            aF0 = a->f0;
            a->f0 = 4;
            aF4 = a->f4;
            a->f4 = 0;
        }
    }
    ~Override()
    {
        if (a) {
            a->f0 = aF0;
            a->f4 = aF4;
        }
        if (b) {
            b->fc = bFC;
            b->f100 = b100;
        }
    }
};
extern "C" void func_00164228(int id)
{
    Obj *obj;
    int err;

    if (func_002852B0(D_004BC230)) {
        err = 0x69;
        goto fail;
    }
    obj = func_0017E1B8(&D_00475480, 0x105, id, 0);
    if (!obj) {
        err = 0x6A;
        goto fail;
    }
    if (obj->x44 < 2) {
        err = 0x7E;
    fail:
        func_00244F08(func_002459F8(err), 0);
        return;
    }
    if (D_00475480.x4044)
        func_00187118(D_00475480.x4044);
    if (func_0025E188() == 8) {
        Override o(obj);
        func_001890B0(obj, 1, 0);
        if (D_00475480.x4044)
            func_00187118(D_00475480.x4044);
        WriteInteger(D_00475480.x407C, obj->x18);
        WriteInteger(D_00475480.x4080, obj->xAC);
    } else {
        Override o(obj);
        func_001890B0(obj, 1, 0);
        func_001890B0(obj, 3, 0);
        if (D_00475480.x4044)
            func_00187118(D_00475480.x4044);
    }
    func_00289070(&D_00475480, func_0025E070(0), 0x1A8, 0, -1);
}
