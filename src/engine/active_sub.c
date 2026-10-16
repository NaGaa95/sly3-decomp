// SLY3_CFLAGS: -Os -G0
struct EngineSubRecord { int first; int active; };
struct EngineSubOwner { unsigned char prefix[0x30]; struct EngineSubRecord sub; };
struct EngineSubHolder { unsigned char prefix[0x50]; struct EngineSubOwner *owner; };
struct EngineSubRecord *func_00173408(struct EngineSubHolder *holder)
{
    struct EngineSubOwner *owner=holder->owner;
    if(!owner->sub.active) return 0;
    return &owner->sub;
}
