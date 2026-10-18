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
struct SubjectBits { unsigned long low : 48; long kind : 4; unsigned long high : 12; };
struct SubjectList { unsigned char prefix[0x80]; void *members; };
struct SubjectKeys { int word; int other; };
struct Action;
struct SubjectSelf {
    unsigned char prefix[0x28]; SubjectBits bits; unsigned char gap30[0x3C - 0x30]; unsigned int tag;
    unsigned char gap40[0x54 - 0x40]; int word54; int word58; unsigned char gap5C[0x64 - 0x5C]; float rate; unsigned char gap68[0x6C - 0x68]; SubjectList *list; int word70;
    unsigned char gap74[0x80 - 0x74]; int *first; int firstCount; int *firstOut; int *second; int secondCount; int *secondOut;
    int word98; Action *word9C; int wordA0, wordA4; unsigned char gapA8[0xD0 - 0xA8]; SubjectKeys keyA; SubjectKeys keyB;
};
struct SubjectGame { unsigned char opaque[1]; };
extern "C" {
extern unsigned char D_00468D30[];
extern SubjectGame D_00475480;
OptionWriteReference QueryWriteOption(KEY *, unsigned char *) __asm__("func_002BC010");
void func_001C7DC8(void *self);
void func_0011AD80(void *list, void *value);
void *func_0017E1B8(void *game, int kind, int id, void *context);
int func_00188A20(void *self);
int func_001880F0(void *self);
void func_00185A70(void *self, int kind, int count, Action *actions);
void func_00185DB0(void *self, int kind, int a, int b, int flag);
void func_001C9118(void *self, int value);
}
static inline int ReadInteger(KEY *key)
{
    return QueryWriteOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_001881F0(SubjectSelf *self)
{
    int i, n;
    func_001C7DC8(self);
    if(self->list) func_0011AD80((char *)self->list + 0x80, self);
    n = 0;
    for(i = 0; i < self->firstCount; i++) {
        void *object = func_0017E1B8(&D_00475480, 0x105, self->first[i], 0);
        if(object) self->firstOut[n++] = (int)object;
    }
    self->firstCount = n;
    n = 0;
    for(i = 0; i < self->secondCount; i++) {
        void *object = func_0017E1B8(&D_00475480, 0x105, self->second[i], 0);
        if(object) self->secondOut[n++] = (int)object;
    }
    self->secondCount = n;
    if(!func_00188A20(self)) {
        if(func_001880F0(self)) {
            func_00185A70(self, 5, self->word98, self->word9C);
            func_00185DB0(self, 5, self->wordA0, self->wordA4, 1);
        }
    }
    {
        KEY *key = (KEY *)&self->keyA;
        if(self->keyA.word) self->word54 = ReadInteger(key);
    }
    {
        KEY *key = (KEY *)&self->keyB;
        if(self->keyB.word) self->word58 = ReadInteger(key);
    }
    if(self->rate != 0.0f || self->word70) {
        int kind = self->bits.kind;
        if(kind == 2) func_001C9118(self, 0);
        if((self->tag ^ 1) & 1) *(unsigned int *)self->tag |= 2;
        else self->tag |= 2;
    }
}
