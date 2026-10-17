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
struct MessageParams { unsigned char prefix[8]; float first; float second; };
struct MessageSelf { unsigned char prefix[8]; KEY *key; unsigned char gapC[4]; int dirty; MessageParams *params; };
struct MessageSource { unsigned char prefix[0x44]; int stage; unsigned char gap48[0x58 - 0x48]; int count; unsigned char gap5C[0x6C - 0x5C]; void *owner; };
struct MessageGlobal { unsigned char prefix[0x70]; int enabled; };
extern "C" {
extern unsigned char D_00468D30[];
struct MessageRoot { void *owner; };
extern MessageRoot D_004794C4;
OptionWriteReference QueryWriteOption(KEY *, unsigned char *) __asm__("func_002BC010");
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &, unsigned char *) __asm__("func_002BC050");
void func_00171D98(MessageSelf *self, float value);
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
static inline int ReadInteger(KEY *key)
{
    return QueryWriteOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_00171AA0(MessageSelf *self, int kind, MessageSource *source)
{
    switch(kind) {
    case 0x29:
        if(D_004794C4.owner == source->owner && source->stage == 2 && source->count == 1) func_00171D98(self, self->params->second);
        break;
    case 0x10:
        WriteInteger(self->key, ReadInteger(self->key) << 1);
        self->dirty = 1;
        break;
    case 0xC:
        WriteInteger(self->key, (ReadInteger(self->key) << 1) | 1);
        self->dirty = 1;
        if(D_004794C4.owner && ((MessageGlobal *)D_004794C4.owner)->enabled) func_00171D98(self, self->params->first);
        break;
    case 0x20:
        func_00171D98(self, self->params->first);
        break;
    }
}
