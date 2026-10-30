// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "../../include/eval_dispatch_api.h"
}
class OptionReadReference {
public:
    CRef value;
    OptionReadReference(const OptionReadReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReadReference() { Drop(); }
};
struct KEY;
struct Action;
struct Notification;
struct SubjectKeys { int word; int other; };
struct Self {
    unsigned char prefix[0x7C]; int word7C;
    unsigned char gap80[0x98 - 0x80];
    int word98; Action *word9C; int wordA0; Notification *wordA4; float realA8; int wordAC;
    unsigned char gapB0[0xD0 - 0xB0]; SubjectKeys keyA; unsigned char gapD8[0xE0 - 0xD8]; SubjectKeys keyB;
    unsigned char keyC[8];
};
extern "C" {
extern unsigned char D_00468D30[];
extern unsigned char D_004793C8[];
OptionReadReference QueryReadOption(KEY *, unsigned char *) __asm__("func_002BC010");
void func_001C7DC8(void *self);
int func_00187CB8(void *self);
int func_00185FD8(void *self);
void func_00185A70(void *self, int kind, int count, Action *actions);
void func_00185DB0(void *self, int kind, int count, Notification *notifications, int flag);
int func_0021C2E0(void *table, void *key, void *context);
}
static inline int ReadInteger(KEY *key)
{
    return QueryReadOption(key, D_00468D30).value.payload.integer;
}
static inline float ReadReal(KEY *key)
{
    return QueryReadOption(key, D_00468D30).value.payload.real;
}
extern "C" void func_00186108(Self *self)
{
    func_001C7DC8(self);
    if (!func_00187CB8(self)) {
        if (func_00185FD8(self)) {
            func_00185A70(self, 5, self->word98, self->word9C);
            func_00185DB0(self, 5, self->wordA0, self->wordA4, 1);
        }
    }
    {
        KEY *key = (KEY *)&self->keyA;
        if (self->keyA.word) self->word7C = ReadInteger(key);
    }
    {
        KEY *key = (KEY *)&self->keyB;
        if (self->keyB.word) self->realA8 = ReadReal(key);
    }
    self->wordAC = func_0021C2E0(D_004793C8, self->keyC, D_00468D30);
}
