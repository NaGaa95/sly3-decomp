// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
struct EnvironmentBinding;
struct EnvironmentBindingLink {
    EnvironmentBinding *value;
    void operator=(EnvironmentBinding *binding) __asm__("func_002BAED0");
};
struct EnvironmentBinding {
    int references;
    unsigned int word4;
    int key;
    CRef value;
    EnvironmentBindingLink next;
    void Destroy(int flags) __asm__("func_002BACE0");
};
struct EnvironmentBindingView {
    unsigned char prefix[0xC];
    EnvironmentBindingLink first;
};
class EnvironmentBindingOwner {
public:
    EnvironmentBinding *value;
    void Set(EnvironmentBinding *binding) __asm__("func_002BAEB0");
    ~EnvironmentBindingOwner() {
        EnvironmentBinding *binding=value;
        if(binding && --binding->references==0)
            binding->Destroy(3);
    }
};
class BindingInsertReference {
public:
    CRef value;
    BindingInsertReference(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~BindingInsertReference() { Drop(); }
};
extern "C" EnvironmentBinding *func_002BAE00();

extern "C" BindingInsertReference func_001299C8(EvalFrame *frame,int key,const CRef *source)
{
    EnvironmentBindingLink *first=&((EnvironmentBindingView *)frame)->first;
    EnvironmentBindingOwner owner;
    owner.Set(func_002BAE00());
    owner.value->key=key;
    func_0012B3B0(&owner.value->value,source);
    owner.value->next=first->value;
    *first=owner.value;
    return BindingInsertReference(0x22);
}
