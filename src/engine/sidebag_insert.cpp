// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
struct SidebagSetOwner;
struct SidebagInsertBinding;
struct SidebagInsertBindingLink {
    SidebagInsertBinding *value;
    void operator=(SidebagInsertBinding *binding) __asm__("func_002BAED0");
};
struct SidebagInsertBinding {
    int references;
    unsigned int word4;
    int key;
    CRef value;
    SidebagInsertBindingLink next;
    void Destroy(int flags) __asm__("func_002BACE0");
};
struct SidebagInsertBindingView {
    unsigned char prefix[0x8];
    SidebagInsertBindingLink first;
};
class SidebagInsertBindingOwner {
public:
    SidebagInsertBinding *value;
    void Set(SidebagInsertBinding *binding) __asm__("func_002BAEB0");
    ~SidebagInsertBindingOwner() {
        SidebagInsertBinding *binding=value;
        if(binding && --binding->references==0)
            binding->Destroy(3);
    }
};
class SidebagInsertReference {
public:
    CRef value;
    SidebagInsertReference(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~SidebagInsertReference() { Drop(); }
};
extern "C" SidebagInsertBinding *func_002BAE00();

extern "C" SidebagInsertReference func_0012C650(SidebagSetOwner *sidebag,int key,const CRef *source)
{
    SidebagInsertBindingLink *first=&((SidebagInsertBindingView *)sidebag)->first;
    SidebagInsertBindingOwner owner;
    owner.Set(func_002BAE00());
    owner.value->key=key;
    func_0012B3B0(&owner.value->value,source);
    owner.value->next=first->value;
    *first=owner.value;
    return SidebagInsertReference(0x22);
}
