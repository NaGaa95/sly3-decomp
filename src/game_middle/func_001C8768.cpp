// SLY3_ASFIX: engine-aligned-loops
// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
struct Link { int unknown00; Link *next; int value; int unknown0C; void *owner; };
struct Chain { char pad00[0x18]; int value; char pad1C[0x1C]; Link *first; };
extern "C" int func_001C8768(Chain *chain, int value)
{
    Link *link;
    if (chain->value == value) return 1;
    for (link = chain->first; link && link->owner == chain; link = link->next)
        if (link->value == value) return 1;
    return 0;
}


