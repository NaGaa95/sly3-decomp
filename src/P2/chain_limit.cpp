// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ChainLink { unsigned char prefix[0x94]; int limit; unsigned char gap98[0xC]; ChainLink *next; };
struct ChainOwner { unsigned char prefix[0x431C]; ChainLink *chain; };
extern "C" void func_002BFD38(void *object,int flags);
class CleanupScope {
public:
    CleanupScope() {}
    ~CleanupScope() { func_002BFD38(this,2); }
};
extern "C" int func_00262128(ChainOwner *owner,int index)
{
    CleanupScope scope;
    for(ChainLink *link=owner->chain;link;link=link->next)
        if(index<link->limit)
            return 1;
    return 0;
}
