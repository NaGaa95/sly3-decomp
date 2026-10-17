// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti -fno-cse-skip-blocks
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
struct GameKeys { unsigned char opaque[0x407C]; KEY *first, *second; };
struct CursorItem { unsigned char prefix[0x5C]; struct CursorItem *selected; unsigned char gap60[0x18 - 0x18]; };
struct CursorTarget { unsigned char prefix[0x18]; int value; unsigned char gap1C[0xAC - 0x1C]; int other; };
struct CursorLink { unsigned char prefix[0x5C]; CursorTarget *target; };
struct CursorItemRef { unsigned char prefix[0x6C]; CursorLink *link; };
struct CursorList { unsigned char prefix[0x90]; int count; CursorItemRef **items; };
struct CursorSelf { unsigned char prefix[0x40]; int mode; unsigned char gap44[0x54 - 0x44]; void *first; CursorList *list; unsigned char gap5C[0x6C - 0x5C]; void *link; unsigned char gap70[0xF8 - 0x70]; int slot; };
extern "C" {
extern unsigned char D_00468D30[];
extern GameKeys D_00475480;
struct CursorGlobal { int value; };
extern CursorGlobal D_0036DBA4;
extern unsigned char D_00375290[];
OptionWriteReference AssignWriteOption(KEY *, const OptionWriteReference &, unsigned char *) __asm__("func_002BC050");
void func_00189B08(void *set, int flag);
void func_0021F5D0(int slot, int enabled);
void func_00186298(void *self);
void func_001734E0(void);
void func_001CFE08(void *object);
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
extern "C" void func_00187270(CursorSelf *self)
{
    CursorTarget *chosen;
    int i;
    if(self->mode == 2) func_00189B08(self->first, 0);
    else if(!self->link) func_00189B08(self->list, 3);
    int none = -1;
    if(self->slot != none) func_0021F5D0(self->slot, 1);
    func_00186298(self);
    chosen = 0;
    func_001734E0();
    D_0036DBA4.value = none;
    for(i = 0; i < self->list->count; i++) {
        CursorLink *link = self->list->items[i]->link;
        if(link) {
            CursorTarget *candidate = link->target;
            if(candidate) chosen = candidate;
        }
    }
    if(chosen) {
        WriteInteger(D_00475480.first, chosen->value);
        WriteInteger(D_00475480.second, chosen->other);
    } else {
        WriteInteger(D_00475480.first, 0);
        WriteInteger(D_00475480.second, 0);
    }
    if(!self->link) func_001CFE08(D_00375290);
}
