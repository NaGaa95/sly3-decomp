// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class SidebagSetReference {
public:
    CRef value;
    SidebagSetReference() { value.tag = -1; }
    SidebagSetReference(const SidebagSetReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    void InitTag(int) __asm__("func_0012BDD8");
    ~SidebagSetReference() { Drop(); }
};
struct SidebagBinding {
    int unused0, unused4;
    int key;
    CRef value;
    SidebagBinding *next;
};
struct SidebagSetOwner { int unused0, unused4; SidebagBinding *bindings; };
extern "C" SidebagSetReference SetSidebagBinding(SidebagSetOwner *,int,const CRef *)
    __asm__("func_0012C718");

extern "C" SidebagSetReference SetSidebagBinding(SidebagSetOwner *owner,int key,const CRef *value)
{
    for (SidebagBinding *binding = owner->bindings; binding; binding = binding->next) {
        if (binding->key == key) {
            SidebagSetReference result;
            func_0012B3B0(&binding->value,value);
            result.Drop();
            result.InitTag(0x22);
            return result;
        }
    }
    SidebagSetReference result;
    result.Drop();
    result.InitTag(0x22);
    return result;
}
